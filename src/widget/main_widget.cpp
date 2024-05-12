#include "widget/main_widget.hpp"

void MainWidget::_onUpdate()
{
	
}

void MainWidget::_onGeometryChange()
{
	_mainMenuPanel.setGeometry(0, size());
}

void MainWidget::_onRender()
{
	
}

MainWidget::MainWidget(spk::Widget* p_parent) :
	MainWidget("Anonymous MainWidget", p_parent)
{
	
}

MainWidget::MainWidget(const std::string& p_name, spk::Widget* p_parent) :
	spk::Widget(p_name, p_parent),
	_textureManagerInstanciator(),
	_mainMenuPanel("MainPanel", this)
{
	_mainMenuPanel.activate();
}