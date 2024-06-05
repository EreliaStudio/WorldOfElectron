#include "widget/panel/host_game_panel.hpp"

#include "widget/main_widget.hpp"

void HostGamePanel::_onUpdate()
{
	
}

void HostGamePanel::_onGeometryChange()
{
	spk::Vector2Int anchor = 0;
	spk::Vector2Int buttonSize = spk::Vector2UInt(std::min(size().x / 4, 400u), std::min(size().y / 15, 80u));
	spk::Vector2Int buttonCornerSize = std::min(buttonSize.x / 20, buttonSize.y / 8);
	
	_confirmButton->setGeometry(anchor, buttonSize);
	_confirmButton->box(Button::State::Pressed).setCornerSize(buttonCornerSize);
	_confirmButton->box(Button::State::Released).setCornerSize(buttonCornerSize);

	_cancelButton->setGeometry(anchor + spk::Vector2Int(buttonSize.x + 10, 0), buttonSize);
	_cancelButton->box(Button::State::Pressed).setCornerSize(buttonCornerSize);
	_cancelButton->box(Button::State::Released).setCornerSize(buttonCornerSize);

	spk::Font::Size fontSize = std::min({
		_confirmButton->computeOptimalFontSize(0.1f, buttonCornerSize.y / 2),
		_cancelButton->computeOptimalFontSize(0.1f, buttonCornerSize.y / 2)
	});

	_confirmButton->label(Button::State::Pressed).setFontSize(fontSize);
	_confirmButton->label(Button::State::Released).setFontSize(fontSize);
	
	_cancelButton->label(Button::State::Pressed).setFontSize(fontSize);
	_cancelButton->label(Button::State::Released).setFontSize(fontSize);
}

void HostGamePanel::_onRender()
{

}

HostGamePanel::HostGamePanel(const std::string& p_name, spk::Widget* p_parent) :
	spk::Panel(p_name, p_parent),
	_confirmButton(makeChild<Button>("Confirm host game button", this)),
	_cancelButton(makeChild<Button>("Cancel host creation button", this))
{
	_confirmButton->setText("Confirm");
	_confirmButton->setOnClickCallback([&](){MainWidget::EventManager::instance()->notify_all(MainWidget::Event::ConfirmGameCreation);});
	_confirmButton->activate();

	_cancelButton->setText("Cancel");
	_cancelButton->setOnClickCallback([&](){MainWidget::EventManager::instance()->notify_all(MainWidget::Event::EnterMainMenu);});
	_cancelButton->activate();
}