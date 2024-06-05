#pragma once

#include <sparkle.hpp>

#include "miscellaneous/widget_redefinition.hpp"

#include "widget/widget/value_selector.hpp"

class HostGamePanel : public spk::Panel
{
private:
	TextLabel* _worldNameLabel;
	TextEntry* _worldNameEntry;
	
	TextLabel* _chunkSizeLabel;
	ValueSelector<int>* _chunkSizeSelector;

	Button* _confirmButton;
	Button* _cancelButton;

	void _updateGeometry();
	void _updateFontSize();

	void _onUpdate() override;
	void _onGeometryChange() override;
	void _onRender() override;

public:
	HostGamePanel(spk::Widget* p_parent) :
		HostGamePanel("Unnamed HostGamePanel", p_parent){}
	HostGamePanel(const std::string& p_name, spk::Widget* p_parent);
};