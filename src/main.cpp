#include "woe.hpp"

class Object : public spk::Entity
{
private:
	spk::Mesh _mesh;
	spk::Material _material;
	spk::MeshRenderer& _renderer;

public:
	Object(const std::wstring& p_name) :
		spk::Entity(p_name),
		_renderer(addComponent<spk::MeshRenderer>(L"Renderer"))
	{
		addTag(L"Object");

		_mesh.addPoint(spk::Vector3(-0.5f, -0.5f, -0.5f)); // 0
		_mesh.addPoint(spk::Vector3(+0.5f, -0.5f, -0.5f)); // 1
		_mesh.addPoint(spk::Vector3(-0.5f, +0.5f, -0.5f)); // 2
		_mesh.addPoint(spk::Vector3(+0.5f, +0.5f, -0.5f)); // 3

		_mesh.addPoint(spk::Vector3(-0.5f, -0.5f, +0.5f)); // 4
		_mesh.addPoint(spk::Vector3(+0.5f, -0.5f, +0.5f)); // 5
		_mesh.addPoint(spk::Vector3(-0.5f, +0.5f, +0.5f)); // 6
		_mesh.addPoint(spk::Vector3(+0.5f, +0.5f, +0.5f)); // 7

		_mesh.addUV(spk::Vector2(0, 0)); // 0
		_mesh.addUV(spk::Vector2(1, 0)); // 1
		_mesh.addUV(spk::Vector2(0, 1)); // 2
		_mesh.addUV(spk::Vector2(1, 1)); // 3

		// Front face (z = -0.5)
        _mesh.addFace(
            spk::Mesh::VertexIndex(0, 0),
            spk::Mesh::VertexIndex(1, 1),
            spk::Mesh::VertexIndex(3, 3),
            spk::Mesh::VertexIndex(2, 2)
        );

        // Back face (z = +0.5)
        _mesh.addFace(
            spk::Mesh::VertexIndex(4, 0),
            spk::Mesh::VertexIndex(6, 1),
            spk::Mesh::VertexIndex(7, 3),
            spk::Mesh::VertexIndex(5, 2)
        );

        // Left face (x = -0.5)
        _mesh.addFace(
            spk::Mesh::VertexIndex(0, 0),
            spk::Mesh::VertexIndex(2, 1),
            spk::Mesh::VertexIndex(6, 3),
            spk::Mesh::VertexIndex(4, 2)
        );

        // Right face (x = +0.5)
        _mesh.addFace(
            spk::Mesh::VertexIndex(1, 0),
            spk::Mesh::VertexIndex(5, 1),
            spk::Mesh::VertexIndex(7, 3),
            spk::Mesh::VertexIndex(3, 2)
        );

        // Top face (y = +0.5)
        _mesh.addFace(
            spk::Mesh::VertexIndex(2, 0),
            spk::Mesh::VertexIndex(3, 1),
            spk::Mesh::VertexIndex(7, 3),
            spk::Mesh::VertexIndex(6, 2)
        );

        // Bottom face (y = -0.5)
        _mesh.addFace(
            spk::Mesh::VertexIndex(0, 0),
            spk::Mesh::VertexIndex(4, 1),
            spk::Mesh::VertexIndex(5, 3),
            spk::Mesh::VertexIndex(1, 2)
        );

		_material.setDiffuse(new spk::Image("resources/texture/diffuseTexture.png"));
		_material.setSpecular(new spk::Image("resources/texture/specularTexture.png"));
		_material.setShininess(0.5f);

		_renderer.setMesh(&_mesh);
		_renderer.setMaterial(&_material);
	}
};

class Player : public spk::Entity
{
private:
	spk::Camera& _camera;

public:
	Player() :
		spk::Entity(L"Player"),
		_camera(addComponent<spk::Camera>(L"MainCamera"))
	{

	}
};

class GameEngineWidget : public spk::Widget
{
private:
	spk::GameEngine _engine;

	Object _cube;
	Player _player;

	void _onPaintEvent(const spk::PaintEvent& p_event) override
	{
		DEBUG_LINE();
		_engine.render();
		DEBUG_LINE();
	}

	void _onUpdateEvent(const spk::UpdateEvent& p_event) override
	{
		_engine.update(p_event.deltaTime);
	}

public:
	GameEngineWidget(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent) :
		spk::Widget(p_name, p_parent),
		_cube(L"Cube"),
		_player()
	{
		DEBUG_LINE();
		_player.transform().place(spk::Vector3(3, 3, 3));
		_cube.transform().place(spk::Vector3(0, 0, 0));
		_player.transform().lookAt(_cube.transform().position());
		DEBUG_LINE();

		_engine.addEntity(&_player);
		_engine.addEntity(&_cube);
		DEBUG_LINE();

		_player.setPriority(1000);
		_cube.setPriority(0);
		DEBUG_LINE();
	}
};

int main()
{
		DEBUG_LINE();
    spk::GraphicalApplication app;

		DEBUG_LINE();
    spk::SafePointer<spk::Window> win = app.createWindow(L"WorldOfElectron", spk::Geometry2D(0, 0, { 600, 600 }));
		DEBUG_LINE();
    win->setUpdateRate(0);

		DEBUG_LINE();
	GameEngineWidget gameEngineWidget = GameEngineWidget(L"GameEngineWidget", win->widget());
	gameEngineWidget.setGeometry(win->geometry());
	gameEngineWidget.activate();
		DEBUG_LINE();

    return app.run();
}
