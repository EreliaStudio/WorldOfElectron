#include "widget/main_menu/main_menu_panel.hpp"

void MainMenuPanel::_onUpdate()
{
	
}

void MainMenuPanel::_onGeometryChange()
{
	spk::Vector2Int selectorSize = spk::Vector2Int(std::min(400.0f, ((size().x) / 3.0f)), std::min(300.0f, ((size().y) / 1.5f)));
	spk::Vector2Int selectorAnchor = (size() - selectorSize) / 2;
	_selectorWidget.setGeometry(selectorAnchor, selectorSize);
}

void MainMenuPanel::_onRender()
{
	
}

MainMenuPanel::MainMenuPanel(spk::Widget* p_parent) :
	MainMenuPanel("Anonymous MainMenuPanel", p_parent)
{

}

MainMenuPanel::MainMenuPanel(const std::string& p_name, spk::Widget* p_parent) :	
	spk::Panel(p_name, p_parent),
	_selectorWidget("Main menu Selector", this)
{
	_selectorWidget.activate();
}