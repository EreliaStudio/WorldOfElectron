#include "widget/main_menu/main_menu_panel.hpp"

void MainMenuPanel::SelectorWidget::_onUpdate()
{
	
}

void MainMenuPanel::SelectorWidget::_onGeometryChange()
{
	_backgroundFrame.setLayer(5);
	_backgroundFrame.setGeometry(0, size());

	spk::Vector2Int titleLabelAnchor = _titleLabel.box().cornerSize();
	spk::Vector2Int titleLabelSize = spk::Vector2Int(size().x - _titleLabel.box().cornerSize().x * 2, _titleLabel.box().cornerSize().y * 5);
	
	_titleLabel.setLayer(10);
	_titleLabel.setGeometry(titleLabelAnchor, titleLabelSize);
	_titleLabel.label().setTextSize(_titleLabel.label().font()->computeOptimalTextSize(_titleLabel.label().text(), _titleLabel.label().outlineSize(), _titleLabel.label().outlineStyle(), titleLabelSize - _titleLabel.box().cornerSize() * 3));

	spk::Vector2Int buttonSize = spk::Vector2Int(
		titleLabelSize.x, 
		(size().y - _titleLabel.box().cornerSize().y * 2 - titleLabelSize.y - 30) / 3
	);
	spk::Vector2Int buttonAnchor = spk::Vector2Int(
		titleLabelAnchor.x,
		titleLabelAnchor.y + titleLabelSize.y + 10
	);
	
	_joinGameButton.setLayer(10);
	_joinGameButton.setGeometry(buttonAnchor + spk::Vector2Int(0, buttonSize.y + 10) * 0, buttonSize);

	_hostGameButton.setLayer(10);
	_hostGameButton.setGeometry(buttonAnchor + spk::Vector2Int(0, buttonSize.y + 10) * 1, buttonSize);

	_quitGameButton.setLayer(10);
	_quitGameButton.setGeometry(buttonAnchor + spk::Vector2Int(0, buttonSize.y + 10) * 2, buttonSize);
}

void MainMenuPanel::SelectorWidget::_onRender()
{
	
}

MainMenuPanel::SelectorWidget::SelectorWidget(spk::Widget* p_parent) :
	SelectorWidget("Anonymous SelectorWidget", p_parent)
{
	
}

MainMenuPanel::SelectorWidget::SelectorWidget(const std::string& p_name, spk::Widget* p_parent) :
	spk::Widget(p_name, p_parent),
	_backgroundFrame("BackgroundFrame", this),
	_titleLabel("Title Background", &_backgroundFrame),
	_joinGameButton("Join game button", &_backgroundFrame),
	_hostGameButton("Host game button", &_backgroundFrame),
	_quitGameButton("Quit game button", &_backgroundFrame)
{
	_backgroundFrame.box().setCornerSize(4);
	_backgroundFrame.activate();

	_titleLabel.label().setFont(TextureManager::instance()->font("TitleFont"));
	_titleLabel.label().setText("World Of Electron");
	_titleLabel.label().setVerticalAlignment(spk::VerticalAlignment::Centered);
	_titleLabel.label().setHorizontalAlignment(spk::HorizontalAlignment::Centered);
	_titleLabel.label().setOutlineStyle(spk::Font::OutlineStyle::None);
	_titleLabel.label().setOutlineColor(spk::Color(230, 62, 96));
	_titleLabel.label().setTextColor(spk::Color(255, 7, 57));

	_titleLabel.box().setSpriteSheet(TextureManager::instance()->spriteSheet("TitleBackground"));
	_titleLabel.box().setCornerSize(16);
	
	_titleLabel.activate();

	_joinGameButton.label(spk::Button::State::Pressed).setText("Join game");
	_joinGameButton.label(spk::Button::State::Released).setText("Join game");
	_joinGameButton.activate();

	_hostGameButton.label(spk::Button::State::Pressed).setText("Host game");
	_hostGameButton.label(spk::Button::State::Released).setText("Host game");
	_hostGameButton.activate();

	_quitGameButton.label(spk::Button::State::Pressed).setText("Quit");
	_quitGameButton.label(spk::Button::State::Released).setText("Quit");
	_quitGameButton.activate();
}