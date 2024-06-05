#pragma once

#include <sparkle.hpp>

class JoinGamePanel : public spk::Panel
{
private:
	void _onUpdate() override;
	void _onGeometryChange() override;
	void _onRender() override;

public:
	JoinGamePanel(spk::Widget* p_parent) :
		JoinGamePanel("Unnamed JoinGamePanel", p_parent){}
	JoinGamePanel(const std::string& p_name, spk::Widget* p_parent);
};