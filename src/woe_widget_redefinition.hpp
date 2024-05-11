#pragma once

#include "sparkle.hpp"

#include "woe_texture_manager.hpp"

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
		box().setSpriteSheet(TextureManager::instance()->spriteSheet("DefaultFrame"));
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
		box().setSpriteSheet(TextureManager::instance()->spriteSheet("DefaultFrame"));
		box().setCornerSize(8);

		label().setFont(TextureManager::instance()->font("DefaultFont"));
		label().setVerticalAlignment(spk::VerticalAlignment::Top);
		label().setHorizontalAlignment(spk::HorizontalAlignment::Left);

		label().setTextSize(25);
		label().setTextColor(spk::Color(255, 255, 255));

		label().setOutlineSize(3);
		label().setOutlineColor(spk::Color(0, 0, 0));
		label().setOutlineStyle(spk::Font::OutlineStyle::Standard);
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
		box().setSpriteSheet(TextureManager::instance()->spriteSheet("DefaultFrame"));
		box().setCornerSize(8);

		label().setFont(TextureManager::instance()->font("DefaultFont"));
		label().setVerticalAlignment(spk::VerticalAlignment::Top);
		label().setHorizontalAlignment(spk::HorizontalAlignment::Left);

		label().setTextSize(25);
		label().setTextColor(spk::Color(255, 255, 255));

		label().setOutlineSize(3);
		label().setOutlineColor(spk::Color(0, 0, 0));
		label().setOutlineStyle(spk::Font::OutlineStyle::Standard);
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
		box(spk::Button::State::Released).setSpriteSheet(TextureManager::instance()->spriteSheet("DefaultFrame"));
		box(spk::Button::State::Released).setCornerSize(8);
		
		box(spk::Button::State::Pressed).setSpriteSheet(TextureManager::instance()->spriteSheet("DarkFrame"));
		box(spk::Button::State::Pressed).setCornerSize(8);
	}
};