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
            spk::Mesh::VertexIndex(2, 2),
            spk::Mesh::VertexIndex(3, 3)
        );

        // // Back face (z = +0.5)
        _mesh.addFace(
            spk::Mesh::VertexIndex(4, 0),
            spk::Mesh::VertexIndex(6, 1),
            spk::Mesh::VertexIndex(5, 2),
            spk::Mesh::VertexIndex(7, 3)
        );

        // // Left face (x = -0.5)
        _mesh.addFace(
            spk::Mesh::VertexIndex(0, 0),
            spk::Mesh::VertexIndex(2, 1),
            spk::Mesh::VertexIndex(4, 2),
            spk::Mesh::VertexIndex(6, 3)
        );

        // // Right face (x = +0.5)
        _mesh.addFace(
            spk::Mesh::VertexIndex(1, 0),
            spk::Mesh::VertexIndex(5, 1),
            spk::Mesh::VertexIndex(3, 2),
            spk::Mesh::VertexIndex(7, 3)
        );

        // // Top face (y = +0.5)
        _mesh.addFace(
            spk::Mesh::VertexIndex(2, 0),
            spk::Mesh::VertexIndex(3, 1),
            spk::Mesh::VertexIndex(6, 2),
            spk::Mesh::VertexIndex(7, 3)
        );

        // // Bottom face (y = -0.5)
        _mesh.addFace(
            spk::Mesh::VertexIndex(0, 0),
            spk::Mesh::VertexIndex(4, 1),
            spk::Mesh::VertexIndex(1, 2),
            spk::Mesh::VertexIndex(5, 3)
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

	spk::Camera& camera()
	{
		return (_camera);
	}
};

class GameEngineWidget : public spk::Widget
{
private:
	spk::GameEngine _engine;

	int _turning = 0;
	Object _cube[4];
	Player _player;

	void _onGeometryChange() override
	{
		float ratio = static_cast<float>(geometry().size.x) / static_cast<float>(geometry().size.y);

		_player.camera().setOrthographic(-5 * ratio, 5 * ratio, -5, 5, 1000.0, 0.1);
		// _player.camera().setPerspective(90.0f, ratio, 1000.0f, 0.1f);
	}

	void _onKeyboardEvent(const spk::KeyboardEvent& p_event) override
	{
		if (p_event.type == spk::KeyboardEvent::Type::Press && p_event.key == spk::Keyboard::A)
		{
			_turning += -1;
		}
		if (p_event.type == spk::KeyboardEvent::Type::Press && p_event.key == spk::Keyboard::Z)
		{
			_turning += 0;
		}
		if (p_event.type == spk::KeyboardEvent::Type::Press && p_event.key == spk::Keyboard::E)
		{
			_turning += 1;
		}
	}

	void _onPaintEvent(const spk::PaintEvent& p_event) override
	{
		_player.getComponent<spk::Camera>().activate();
		_engine.render();
	}

	void _onUpdateEvent(const spk::UpdateEvent& p_event) override
	{
		if (p_event.deltaTime != 0)
		{
			float delta = 0.0180f * static_cast<float>(p_event.deltaTime) * _turning;
			_player.transform().rotateAroundPoint(spk::Vector3(0, 0, 0), spk::Vector3(0, 1, 0), delta);
			_player.transform().lookAt(spk::Vector3(0, 0, 0));

			// _cube[1].transform().rotate(spk::Vector3(delta, 0, 0));
			// _cube[2].transform().rotate(spk::Vector3(0, delta, 0));
			// _cube[3].transform().rotate(spk::Vector3(0, 0, delta));
		}

		_engine.update(p_event.deltaTime);
		p_event.requestPaint();
	}

public:
	GameEngineWidget(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent) :
		spk::Widget(p_name, p_parent),
		_cube{
			Object(L"Cube A"),
			Object(L"Cube B"),
			Object(L"Cube C"),
			Object(L"Cube D"),
		},
		_player()
	{
		_player.transform().place(spk::Vector3(5, 5, 5));

		_cube[0].transform().place(spk::Vector3(0, 0, 0));
		_cube[0].transform().setScale(spk::Vector3(1, 1, 1));

		_cube[1].transform().place(spk::Vector3(1, 0, 0));
		_cube[1].transform().setScale(spk::Vector3(2, 1, 1));

		_cube[2].transform().place(spk::Vector3(0, 1, 0));
		_cube[2].transform().setScale(spk::Vector3(1, 2, 1));

		_cube[3].transform().place(spk::Vector3(0, 0, 1));
		_cube[3].transform().setScale(spk::Vector3(1, 1, 2));
		
		_player.transform().lookAt(_cube[0].transform().position());

		_engine.addEntity(&_player);
		_engine.addEntity(&_cube[0]);
		_engine.addEntity(&_cube[1]);
		_engine.addEntity(&_cube[2]);
		_engine.addEntity(&_cube[3]);

		_player.setPriority(1000);
		_cube[0].setPriority(0);
		_cube[1].setPriority(0);
		_cube[2].setPriority(0);
		_cube[3].setPriority(0);
	}
};

int main()
{
    spk::GraphicalApplication app;

    spk::SafePointer<spk::Window> win = app.createWindow(L"WorldOfElectron", spk::Geometry2D(0, 0, { 600, 600 }));

	GameEngineWidget gameEngineWidget = GameEngineWidget(L"GameEngineWidget", win->widget());
	gameEngineWidget.setGeometry(win->geometry());
	gameEngineWidget.activate();

    return app.run();
}
