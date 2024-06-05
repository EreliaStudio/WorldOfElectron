#include "widget/panel/main_menu_panel.hpp"

#include "widget/main_widget.hpp"

void MainMenuPanel::_onGeometryChange()
{
	spk::Vector2Int buttonSize = spk::Vector2UInt(std::min(size().x / 4, 400u), std::min(size().y / 15, 80u));
	spk::Vector2Int buttonCornerSize = std::min(buttonSize.x / 20, buttonSize.y / 8);

	spk::Vector2Int buttonSpace = spk::Vector2Int(0, 20);
	spk::Vector2Int buttonAnchor = (size() - spk::Vector2Int(buttonSize.x, 0)) / 2;

	_joinButton->setGeometry(buttonAnchor + spk::Vector2Int(0, (buttonSize.y + buttonSpace.y) * 0), buttonSize);
	_joinButton->box(Button::State::Pressed).setCornerSize(buttonCornerSize);
	_joinButton->box(Button::State::Released).setCornerSize(buttonCornerSize);

	_hostButton->setGeometry(buttonAnchor + spk::Vector2Int(0, (buttonSize.y + buttonSpace.y) * 1), buttonSize);
	_hostButton->box(Button::State::Pressed).setCornerSize(buttonCornerSize);
	_hostButton->box(Button::State::Released).setCornerSize(buttonCornerSize);

	_quitButton->setGeometry(buttonAnchor + spk::Vector2Int(0, (buttonSize.y + buttonSpace.y) * 2), buttonSize);
	_quitButton->box(Button::State::Pressed).setCornerSize(buttonCornerSize);
	_quitButton->box(Button::State::Released).setCornerSize(buttonCornerSize);

	spk::Font::Size buttonFontSize = std::min({
		_joinButton->computeOptimalFontSize(0.1f, buttonCornerSize.y / 2),
		_hostButton->computeOptimalFontSize(0.1f, buttonCornerSize.y / 2),
		_quitButton->computeOptimalFontSize(0.1f, buttonCornerSize.y / 2)
	});

	_joinButton->label(Button::State::Pressed).setFontSize(buttonFontSize);
	_joinButton->label(Button::State::Released).setFontSize(buttonFontSize);
	
	_hostButton->label(Button::State::Pressed).setFontSize(buttonFontSize);
	_hostButton->label(Button::State::Released).setFontSize(buttonFontSize);
	
	_quitButton->label(Button::State::Pressed).setFontSize(buttonFontSize);
	_quitButton->label(Button::State::Released).setFontSize(buttonFontSize);

	spk::Vector2Int titleLabelSize = spk::Vector2Int(size().x / 4 * 3, buttonAnchor.y / 3 * 2);
	spk::Vector2Int titleLabelAnchor = spk::Vector2Int(size().x - titleLabelSize.x, buttonAnchor.y - titleLabelSize.y) / 2;
	_titleLabel->setGeometry(titleLabelAnchor, titleLabelSize);
	_titleLabel->label().setFontSize(_titleLabel->computeOptimalFontSize(0.1f));
}

MainMenuPanel::MainMenuPanel(spk::Widget* p_parent) :
	MainMenuPanel("Unnamed MainMenuPanel", p_parent)
{
	
}

MainMenuPanel::MainMenuPanel(const std::string& p_name, spk::Widget* p_parent) :
	spk::Panel(p_name, p_parent)
{
	_titleLabel = makeChild<TextLabel>("TitleLabel", this);
	_titleLabel->label().setText("World of Electrons");
	_titleLabel->label().setVerticalAlignment(spk::VerticalAlignment::Centered);
	_titleLabel->label().setHorizontalAlignment(spk::HorizontalAlignment::Centered);
	_titleLabel->label().setTextColor(spk::Color(155, 207, 209));
	_titleLabel->label().setOutlineColor(spk::Color(85, 155, 158));
	_titleLabel->box().setSpriteSheet(nullptr);
	_titleLabel->box().setCornerSize(0);
	_titleLabel->activate();
	_titleLabel->setLayer(20);

	_joinButton = makeChild<Button>("JoinButton", this);
	_joinButton->setOnClickCallback([](){MainWidget::EventManager::instance()->notify_all(MainWidget::Event::EnterJoinMenu);});
	_joinButton->box(Button::State::Pressed).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_DarkCyan"));
	_joinButton->box(Button::State::Released).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_Cyan"));
	_joinButton->label(Button::State::Pressed).setText("Join game");
	_joinButton->label(Button::State::Released).setText("Join game");
	_joinButton->activate();
	_joinButton->setLayer(20);

	_hostButton = makeChild<Button>("HostButton", this);
	_hostButton->setOnClickCallback([](){MainWidget::EventManager::instance()->notify_all(MainWidget::Event::EnterHostMenu);});
	_hostButton->box(Button::State::Pressed).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_DarkCyan"));
	_hostButton->box(Button::State::Released).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_Cyan"));
	_hostButton->label(Button::State::Pressed).setText("Host game");
	_hostButton->label(Button::State::Released).setText("Host game");
	_hostButton->activate();
	_hostButton->setLayer(20);

	_quitButton = makeChild<Button>("QuitButton", this);
	_quitButton->setOnClickCallback([](){MainWidget::EventManager::instance()->notify_all(MainWidget::Event::QuitGame);});
	_quitButton->box(Button::State::Pressed).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_DarkCyan"));
	_quitButton->box(Button::State::Released).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_Cyan"));
	_quitButton->label(Button::State::Pressed).setText("Quit");
	_quitButton->label(Button::State::Released).setText("Quit");
	_quitButton->activate();
	_quitButton->setLayer(20);

}