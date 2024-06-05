#pragma once

#include <sparkle.hpp>
#include "miscellaneous/widget_redefinition.hpp"

class MainMenuPanel : public spk::Panel
{
private:
	TextLabel* _titleLabel;
	Button* _joinButton;
	
	Button* _hostButton;
	Button* _quitButton;
	void _onGeometryChange() override;

public:
	MainMenuPanel(spk::Widget* p_parent);
	MainMenuPanel(const std::string& p_name, spk::Widget* p_parent);
};