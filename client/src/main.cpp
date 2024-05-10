#include "woe.hpp"

class CustomTextureManager : public spk::TextureManager
{
private:
	std::map<std::string, spk::Font*> _fonts;

public:
	CustomTextureManager()
	{
		loadSpriteSheet("DefaultFrame", "client/resources/texture/frame.png", spk::Vector2UInt(3, 3));
	}

	~CustomTextureManager()
	{
		for (auto& [key, element] : _fonts)
		{
			delete element;
		}
	}

	spk::Font* loadFont(const std::string& p_fontName, const std::filesystem::path& p_fontPath)
	{
		if (_fonts.contains(p_fontName) == true)
			spk::throwException("Can't load a font named [" + p_fontName + "] inside TextureManager : font already loaded");
		_fonts[p_fontName] = new spk::Font(p_fontPath);
	}

	spk::Font* font(const std::string& p_fontName)
	{
		if (_fonts.contains(p_fontName) == false)
			spk::throwException("Can't return a font named [" + p_fontName + "] inside TextureManager\nNo font loaded with desired name");
		return (_fonts[p_fontName]);
	}
};

using TextureManager = spk::Singleton<CustomTextureManager>;

class MainMenuPanel : public spk::Widget
{
private:
	spk::Frame _backgroundFrame;

	void _onUpdate()
	{
		
	}

	void _onGeometryChange()
	{
		_backgroundFrame.setGeometry(0, size());
	}

	void _onRender()
	{
		
	}

public:
	MainMenuPanel(spk::Widget* p_parent) : MainMenuPanel("Anonymous MainMenuPanel", p_parent){}

	MainMenuPanel(const std::string& p_name, spk::Widget* p_parent) :
		spk::Widget(p_name, p_parent),
		_backgroundFrame("BackgroundFrame", this)
	{
		_backgroundFrame.box().setSpriteSheet(TextureManager::instance()->spriteSheet("DefaultFrame"));
		_backgroundFrame.box().setCornerSize(32);
		_backgroundFrame.activate();
	}
};

class MainWidget : public spk::Widget
{
private:
	TextureManager::Instanciator _textureManagerInstanciator;
	MainMenuPanel _mainMenu;

	void _onUpdate()
	{
		
	}

	void _onGeometryChange()
	{
		_mainMenu.setGeometry(0, size());
	}

	void _onRender()
	{
		
	}

public:
	MainWidget(spk::Widget* p_parent) : MainWidget("Anonymous MainWidget", p_parent){}

	MainWidget(const std::string& p_name, spk::Widget* p_parent) :
		spk::Widget(p_name, p_parent),
		_mainMenu("MainMenu", this)
	{
		_mainMenu.activate();
	}
};

int main()
{
    spk::Application app = spk::Application("World Of Electron", spk::Vector2UInt(800, 640), spk::Application::Mode::Multithread);

	MainWidget mainWidget(nullptr);
	mainWidget.setGeometry(0, app.size());
	mainWidget.activate();

    return (app.run());
}