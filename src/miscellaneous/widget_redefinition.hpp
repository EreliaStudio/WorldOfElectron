#pragma once

#include <sparkle.hpp>

#include "texture_atlas.hpp"

class Frame : public spk::Frame
{
private:

public:
	Frame(Widget* p_parent) :
		Frame("Anonymous Frame", p_parent)
	{

	}
	Frame(const std::string& p_name, Widget* p_parent) :
		spk::Frame(p_name, p_parent)
	{
		box().setSpriteSheet(TextureAtlas::instance()->spriteSheet("DefaultFrame"));
		box().setCornerSize(8);
	}
};

class TextLabel : public spk::TextLabel
{
private:

public:
	TextLabel(Widget* p_parent) :
		TextLabel("Anonymous TextLabel", p_parent)
	{

	}
	TextLabel(const std::string& p_name, Widget* p_parent) :
		spk::TextLabel(p_name, p_parent)
	{
		box().setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_Gray"));
		box().setCornerSize(8);

		label().setFont(TextureAtlas::instance()->font("Pixellari"));
		label().setVerticalAlignment(spk::VerticalAlignment::Top);
		label().setHorizontalAlignment(spk::HorizontalAlignment::Left);

		label().setTextSize(25);
		label().setTextColor(spk::Color(255, 255, 255));

		label().setOutlineSize(3);
		label().setOutlineColor(spk::Color(0, 0, 0));
	}
};

class TextEntry : public spk::TextEntry
{
private:

public:
	TextEntry(Widget* p_parent) :
		TextEntry("Anonymous TextEntry", p_parent)
	{

	}
	TextEntry(const std::string& p_name, Widget* p_parent) :
		spk::TextEntry(p_name, p_parent)
	{
		box().setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_Gray"));
		box().setCornerSize(8);

		setPlaceholder("Enter text ...");

		label().setFont(TextureAtlas::instance()->font("Pixellari"));
		label().setVerticalAlignment(spk::VerticalAlignment::Top);
		label().setHorizontalAlignment(spk::HorizontalAlignment::Left);

		label().setTextSize(25);
		label().setTextColor(spk::Color(255, 255, 255));

		label().setOutlineSize(3);
		label().setOutlineColor(spk::Color(0, 0, 0));
	}
};

class Button : public spk::Button
{
private:

public:
	Button(Widget* p_parent) :
		Button("Anonymous Button", p_parent)
	{

	}
	Button(const std::string& p_name, Widget* p_parent) :
		spk::Button(p_name, p_parent)
	{
		box(spk::Button::State::Released).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_Gray"));
		box(spk::Button::State::Released).setCornerSize(8); 
		
		box(spk::Button::State::Pressed).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_DarkGray"));
		box(spk::Button::State::Pressed).setCornerSize(8);

		label(spk::Button::State::Released).setFont(TextureAtlas::instance()->font("Pixellari"));
		label(spk::Button::State::Released).setVerticalAlignment(spk::VerticalAlignment::Centered);
		label(spk::Button::State::Released).setHorizontalAlignment(spk::HorizontalAlignment::Centered);

		label(spk::Button::State::Released).setTextSize(25);
		label(spk::Button::State::Released).setTextColor(spk::Color(255, 255, 255));

		label(spk::Button::State::Released).setOutlineSize(1);
		label(spk::Button::State::Released).setOutlineColor(spk::Color(0, 0, 0));
		
		label(spk::Button::State::Pressed).setFont(TextureAtlas::instance()->font("Pixellari"));
		label(spk::Button::State::Pressed).setVerticalAlignment(spk::VerticalAlignment::Centered);
		label(spk::Button::State::Pressed).setHorizontalAlignment(spk::HorizontalAlignment::Centered);

		label(spk::Button::State::Pressed).setTextSize(23);
		label(spk::Button::State::Pressed).setTextColor(spk::Color(200, 200, 200));

		label(spk::Button::State::Pressed).setOutlineSize(1);
		label(spk::Button::State::Pressed).setOutlineColor(spk::Color(0, 0, 0));
	}
};