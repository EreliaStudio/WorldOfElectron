#pragma once

#include <sparkle.hpp>

#include "miscellaneous/widget_redefinition.hpp"

class HostGamePanel : public spk::Panel
{
private:
	Button* _confirmButton;
	Button* _cancelButton;

	void _onUpdate() override;
	void _onGeometryChange() override;
	void _onRender() override;

public:
	HostGamePanel(spk::Widget* p_parent) :
		HostGamePanel("Unnamed HostGamePanel", p_parent){}
	HostGamePanel(const std::string& p_name, spk::Widget* p_parent);
};