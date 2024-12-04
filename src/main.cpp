#include "woe.hpp"

struct Context : public spk::Singleton<Context>
{
	spk::Client client;
	spk::Server server;

	World world;
	spk::SafePointer<Entity> player = nullptr;
};

class WorldRenderer : public spk::Widget
{
private:
	struct BakedChunk
	{
	static inline std::string PipelineCode = R"(## LAYOUTS DEFINITION ##
0 Vector2 modelPosition


## FRAMEBUFFER DEFINITION ##
0 Color pixelColor


## CONSTANTS DEFINITION ##
CameraConstants_Type CameraConstants 64 64 {
    MVP 0 64 0 64 1 0 {}
}
NodeConstants_Type NodeConstants 4100 4112 {
    nbNodes 0 4 0 4 1 0 {}
    nodes 4 16 16 16 256 0 {
        color 0 16 0 16 1 0 {
            r 0 4 0 4 1 0 {}
            g 4 4 4 4 1 0 {}
            b 8 4 8 4 1 0 {}
            a 12 4 12 4 1 0 {}
        }
    }
}


## ATTRIBUTES DEFINITION ##
ChunkInformations_Type ChunkInformations 3080 3080 {
    position 0 8 0 8 1 0 {
        x 0 4 0 4 1 0 {}
        y 4 4 4 4 1 0 {}
    }
    content 8 4 8 4 768 0 {}
}


## TEXTURES DEFINITION ##


## VERTEX SHADER CODE ##
#version 450

layout (location = 0) in vec2 modelPosition;
layout (location = 0) out flat int out_instanceID;
layout (location = 1) out flat int nodeID;

struct Node
{
    vec4 color;
};

layout(constants) uniform CameraConstants_Type
{
    mat4 MVP;
} CameraConstants;

layout(attributes) uniform ChunkInformations_Type
{
    ivec2 position;
    int content[16][16][3];
} ChunkInformations;

void main()
{
    int nodeLayer = (gl_InstanceID / 256);
    int nodePositionIndex = (gl_InstanceID % 256);
    ivec2 nodePosition = ivec2(nodePositionIndex % 16, nodePositionIndex / 16);
    gl_Position = CameraConstants.MVP * vec4(
		(modelPosition.x + (ChunkInformations.position.x * 16)) + nodePosition.x,
		(modelPosition.y + (ChunkInformations.position.y * 16)) + nodePosition.y,
		nodeLayer,
		1
	);
    nodeID = ChunkInformations.content[nodePosition.x][nodePosition.y][nodeLayer];
    out_instanceID = gl_InstanceID;
}

## FRAGMENT SHADER CODE ##
#version 450

layout (location = 0) in flat int instanceID;
layout (location = 1) in flat int nodeID;
layout (location = 0) out vec4 pixelColor;

struct Node
{
    vec4 color;
};

layout(constants) uniform NodeConstants_Type
{
    int nbNodes;
    Node nodes[256];
} NodeConstants;

void main()
{
    pixelColor = NodeConstants.nodes[nodeID].color;
}

)";
		static inline spk::Pipeline Pipeline = spk::Pipeline(PipelineCode);

		spk::Pipeline::Object object;
		spk::Pipeline::Object::Attribute& attributes;
		spk::Pipeline::Object::Attribute::Element& positionElement;
		spk::Pipeline::Object::Attribute::Element& contentElement;

		BakedChunk() :
			object(Pipeline.createObject()),
			attributes(object.attribute(L"ChunkInformations")),
			positionElement(attributes[L"position"]),
			contentElement(attributes[L"content"])
		{
			std::vector<spk::Vector2> vertices = {
				spk::Vector2(0, 0),
				spk::Vector2(0, 1),
				spk::Vector2(1, 0),
				spk::Vector2(1, 1)
			};

			std::vector<unsigned int> indexes =  {
				0, 1, 2, 2, 1, 3
			};

			object.layout().clear();
			object.indexes().clear();

			object.layout() << vertices;
			object.indexes() << indexes;

			object.layout().validate();
			object.indexes().validate();
		}

		void setPosition(const spk::Vector2Int& p_position)
		{
			positionElement = p_position;
		}

		void bake(const Chunk& p_chunk)
		{
			for (size_t i = 0; i < p_chunk.Size.x; i++)
			{
				for (size_t j = 0; j < p_chunk.Size.y; j++)
				{
					for (size_t h = 0; h < p_chunk.MaxLayer; h++)
					{
						contentElement[i * p_chunk.Size.y * p_chunk.MaxLayer + j * p_chunk.MaxLayer + h] = p_chunk.content[i][j][h];
					}	
				}	
			}
		}

		void validate()
		{
			attributes.validate();
		}

		void render()
		{
			object.render();
		}
	};

	std::unordered_map<spk::Vector2Int, BakedChunk> _bakedChunks;

	void bakeChunk(const spk::Vector2Int& p_chunkPosition, const Chunk& p_chunk)
	{
		BakedChunk newBakedChunk;

		newBakedChunk.setPosition(p_chunkPosition * Chunk::Size);
		newBakedChunk.bake(p_chunk);
		newBakedChunk.validate();

		_bakedChunks.emplace(p_chunkPosition, std::move(newBakedChunk));
	}

	void _onPaintEvent(const spk::PaintEvent& p_event)
	{
		for (auto& [key, chunk] : Context::instance()->world.chunks())
		{
			if (_bakedChunks.contains(key) == false)
			{
				bakeChunk(key, chunk);
			}
			_bakedChunks[key].render();
		}
	}

	Context::Instanciator contextInstanciator;
	EventNotifier::Instanciator eventNotifierInstanciator;

	EventNotifier::Type::Contract nodeConstantsContract;
	spk::Pipeline::Constant& nodeConstants;
	spk::Pipeline::Constant::Element& nbNodesElement;
	spk::Pipeline::Constant::Element& nodesElement;

	EventNotifier::Type::Contract cameraConstantsContract;
	spk::Pipeline::Constant& cameraConstants;
	spk::Pipeline::Constant::Element& MVPElement;

public:
	WorldRenderer(const std::wstring& p_name, const spk::SafePointer<Widget>& p_owner = nullptr) : 
		spk::Widget(p_name, p_owner),
		nodeConstants(BakedChunk::Pipeline.constants(L"NodeConstants")),
		cameraConstants(BakedChunk::Pipeline.constants(L"CameraConstants")),
		nbNodesElement(nodeConstants[L"nbNodes"]),
		nodesElement(nodeConstants[L"nodes"]),
		MVPElement(cameraConstants[L"MVP"])
	{
		nodeConstantsContract = EventNotifier::instance()->subscribe(Event::NodeListEdited, [&](){
			nbNodesElement = static_cast<int>(Context::instance()->world.nodes().size());
			
			for (size_t i = 0; i < Context::instance()->world.nodes().size(); i++)
			{
				nodesElement[i] = Context::instance()->world.node(i)->color;
			}

			nodeConstants.validate();
		});

		cameraConstantsContract = EventNotifier::instance()->subscribe(Event::CameraEdited, [&](){

			if (Context::instance()->player == nullptr)
				throw std::runtime_error("No player defined when updating the camera constants");

			MVPElement = spk::Matrix4x4::ortho(
				Context::instance()->player->position.x - 16,
				Context::instance()->player->position.x + 16,
				Context::instance()->player->position.y - 16,
				Context::instance()->player->position.y + 16, 
				1000, 0);

			cameraConstants.validate();
		});

		EventNotifier::instance()->notifyEvent(Event::NodeListEdited);
		EventNotifier::instance()->notifyEvent(Event::CameraEdited);
	}
};

class WorldManager : public spk::Widget
{
private:
	void _onUpdateEvent(const spk::UpdateEvent& p_event)
	{
		if (p_event.deltaTime == 0)
			return ;

		bool needRepaint = false;

		for (const auto& [c_key, c_entity] : Context::instance()->world.entities())
		{
			if (c_entity.velocity != 0)
			{
				needRepaint = true;

				auto entity = Context::instance()->world.entity(c_key);
				entity->position += entity->velocity * p_event.deltaTime;
			}
		}

		if (needRepaint == true)
		{
			p_event.requestPaint();
		}
	}

public:
	WorldManager(const std::wstring& p_name, const spk::SafePointer<Widget>& p_owner = nullptr) : 
		spk::Widget(p_name, p_owner)
	{

	}
};

int main()
{
    spk::GraphicalApplication app;

    spk::SafePointer<spk::Window> win = app.createWindow(L"WorldOfElectron", spk::Geometry2D(0, 0, { 600, 600 }));
    win->setUpdateRate(0);

	Context::instanciate();

	Context::instance()->server.start(25500);
	Context::instance()->client.connect("127.0.0.1", 25500);

	Context::instance()->world.requestChunk(spk::Vector2Int(1, 1));
	Context::instance()->world.requestChunk(spk::Vector2Int(0, 1));
	Context::instance()->world.requestChunk(spk::Vector2Int(-1, 1));

	Context::instance()->world.requestChunk(spk::Vector2Int(1, 0));
	Context::instance()->world.requestChunk(spk::Vector2Int(0, 0));
	Context::instance()->world.requestChunk(spk::Vector2Int(-1, 0));

	Context::instance()->world.requestChunk(spk::Vector2Int(1, -1));
	Context::instance()->world.requestChunk(spk::Vector2Int(0, -1));
	Context::instance()->world.requestChunk(spk::Vector2Int(-1, -1));

	Context::instance()->player = Context::instance()->world.requestEntity(0);


	ServerWidget serverWidget = ServerWidget(L"ServerWidget", Context::instance()->server, win->widget());
	serverWidget.activate();

	ClientWidget clientWidget = ClientWidget(L"ClientWidget", Context::instance()->client, win->widget());
	clientWidget.activate();

	WorldRenderer worldRenderer = WorldRenderer(L"World renderer", win->widget());
	worldRenderer.setGeometry({0, 0}, win->geometry().size);
	worldRenderer.activate();

	WorldManager worldManager = WorldManager(L"World manager", win->widget());
	worldManager.activate();

    return app.run();
}
