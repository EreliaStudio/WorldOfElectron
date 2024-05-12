#pragma once

#include "miscellaneous/woe_texture_manager.hpp"
#include "widget/main_menu/main_menu_panel.hpp"

class MainWidget : public spk::Widget
{
private:
	TextureManager::Instanciator _textureManagerInstanciator;

	MainMenuPanel _mainMenuPanel;

	void _onUpdate();
	void _onGeometryChange();
	void _onRender();

public:
	MainWidget(spk::Widget* p_parent);
	MainWidget(const std::string& p_name, spk::Widget* p_parent);
};