#pragma once

#include "miscellaneous/woe_texture_atlas.hpp"

#include "widget/panel/main_menu_panel.hpp"

class MainWidget : public spk::Widget
{
private:
	TextureAtlas::Instanciator _textureAtlasInstanciator;

	MainMenuPanel* _mainMenuPanel;

	void _onGeometryChange();

public:
	MainWidget(spk::Widget* p_parent);
	MainWidget(const std::string& p_name, spk::Widget* p_parent);
};