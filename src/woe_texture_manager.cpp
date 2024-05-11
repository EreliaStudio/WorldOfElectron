#include "woe_texture_manager.hpp"

CustomTextureManager::CustomTextureManager()
{
	loadSpriteSheet("DefaultFrame", "resources/texture/frame.png", spk::Vector2UInt(3, 3));
	loadSpriteSheet("DarkFrame", "resources/texture/frameDark.png", spk::Vector2UInt(3, 3));

	loadFont("DefaultFont", "resources/font/Roboto-Regular.ttf");
}

CustomTextureManager::~CustomTextureManager()
{
	for (auto& [key, element] : _fonts)
	{
		delete element;
	}
}

spk::Font* CustomTextureManager::loadFont(const std::string& p_fontName, const std::filesystem::path& p_fontPath)
{
	if (_fonts.contains(p_fontName) == true)
		spk::throwException("Can't load a font named [" + p_fontName + "] inside TextureManager : font already loaded");
	_fonts[p_fontName] = new spk::Font(p_fontPath);
	return (_fonts[p_fontName]);
}

spk::Font* CustomTextureManager::font(const std::string& p_fontName)
{
	if (_fonts.contains(p_fontName) == false)
		spk::throwException("Can't return a font named [" + p_fontName + "] inside TextureManager\nNo font loaded with desired name");
	return (_fonts[p_fontName]);
}