#pragma once

#include "sparkle.hpp"

#include "miscellaneous/woe_widget_redefinition.hpp"

class MainMenuPanel : public spk::Panel
{
private:
	class SelectorWidget : public spk::Widget
	{
	private:
		Frame _backgroundFrame;
		TextLabel _titleLabel;
		Button _joinGameButton;
		Button _hostGameButton;
		Button _quitGameButton;

		void _onUpdate();
		void _onGeometryChange();
		void _onRender();
	
	public:
		SelectorWidget(spk::Widget* p_parent);
		SelectorWidget(const std::string& p_name, spk::Widget* p_parent);
	};
	
	SelectorWidget _selectorWidget;

	void _onUpdate();
	void _onGeometryChange();
	void _onRender();

public:
	MainMenuPanel(spk::Widget* p_parent);
	MainMenuPanel(const std::string& p_name, spk::Widget* p_parent);
};