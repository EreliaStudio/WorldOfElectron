#include "texture_atlas.hpp"

TextureAtlas::TextureAtlas()
{
	loadSpriteSheet("UI.Frame_LightGray", "resources/texture/UI/Frame_LightGray.png", spk::Vector2UInt(3, 3));
	loadSpriteSheet("UI.Frame_Gray", "resources/texture/UI/Frame_Gray.png", spk::Vector2UInt(3, 3));
	loadSpriteSheet("UI.Frame_DarkGray", "resources/texture/UI/Frame_DarkGray.png", spk::Vector2UInt(3, 3));

	loadSpriteSheet("UI.Frame_LightCyan", "resources/texture/UI/Frame_LightCyan.png", spk::Vector2UInt(3, 3));
	loadSpriteSheet("UI.Frame_Cyan", "resources/texture/UI/Frame_Cyan.png", spk::Vector2UInt(3, 3));
	loadSpriteSheet("UI.Frame_DarkCyan", "resources/texture/UI/Frame_DarkCyan.png", spk::Vector2UInt(3, 3));

	loadImage("MainMenu.Background", "resources/texture/illustration/MainMenuBackground.png");

	loadFont("Arial", "resources/font/light-arial.ttf");
	loadFont("DOS", "resources/font/Perfect DOS VGA 437 Win.ttf");
	loadFont("Pixellari", "resources/font/Pixellari.ttf");
	loadFont("advanced_pixel_lcd-7", "resources/font/advanced_pixel_lcd-7.ttf");
}