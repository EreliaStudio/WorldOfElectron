#include "widget/panel/host_game_panel.hpp"

#include "widget/main_widget.hpp"

void HostGamePanel::_onUpdate()
{
	
}

void HostGamePanel::_updateGeometry()
{
	spk::Vector2Int availibleArea = spk::Vector2Int::min(spk::Vector2Int(800, 300), size() - 50);
	spk::Vector2 cellSize = availibleArea / spk::Vector2(40, 15); 
	spk::Vector2Int areaAnchor = (size() - availibleArea) / 2;

	/* Name section */	
	_worldNameLabel->setGeometry(areaAnchor + cellSize * spk::Vector2Int(0, 0), cellSize * spk::Vector2Int(10, 2));
	_worldNameLabel->box().setCornerSize(cellSize / 4);
	
	_worldNameEntry->setGeometry(areaAnchor + cellSize * spk::Vector2Int(11, 0), cellSize * spk::Vector2Int(29, 2));
	_worldNameEntry->box().setCornerSize(cellSize / 4);

	/* Size section */	
	_chunkSizeLabel->setGeometry(areaAnchor + cellSize * spk::Vector2Int(0, 3), cellSize * spk::Vector2Int(10, 2));
	_chunkSizeLabel->box().setCornerSize(cellSize / 4);
	
	_chunkSizeSelector->forceGeometryChange(areaAnchor + cellSize * spk::Vector2Int(11, 3), cellSize * spk::Vector2Int(29, 2));
	_chunkSizeSelector->setCornerSize(cellSize / 4);

	/* Button section */
	_confirmButton->setGeometry(areaAnchor + cellSize * spk::Vector2Int(18, 13), cellSize * spk::Vector2Int(10, 2));
	_confirmButton->box(Button::State::Pressed).setCornerSize(cellSize / 4);
	_confirmButton->box(Button::State::Released).setCornerSize(cellSize / 4);

	_cancelButton->setGeometry(areaAnchor + cellSize * spk::Vector2Int(30, 13), cellSize * spk::Vector2Int(10, 2));
	_cancelButton->box(Button::State::Pressed).setCornerSize(cellSize / 4);
	_cancelButton->box(Button::State::Released).setCornerSize(cellSize / 4);
}

void HostGamePanel::_updateFontSize()
{
	spk::Vector2Int availibleArea = spk::Vector2Int::min(spk::Vector2Int(800, 600), size() - 50);
	spk::Vector2 cellSize = availibleArea / spk::Vector2(40, 30); 
	spk::Vector2 padding = 0;//cellSize.y / 16;

	spk::Font::Size fontSize = std::min({
		_confirmButton->computeOptimalFontSize(0.1f, padding),
		_cancelButton->computeOptimalFontSize(0.1f, padding),
		_worldNameLabel->computeOptimalFontSize(0.1f, padding),
		_chunkSizeLabel->computeOptimalFontSize(0.1f, padding),
		_chunkSizeSelector->computeOptimalFontSize(0.1f, padding)
	});

	_worldNameLabel->label().setFontSize(fontSize);
	_worldNameEntry->label().setFontSize(fontSize);
	_chunkSizeLabel->label().setFontSize(fontSize);
	_chunkSizeSelector->setFontSize(fontSize);
	_chunkSizeSelector->setValueLabelPadding(padding);
	_confirmButton->label(Button::State::Pressed).setFontSize(fontSize);
	_confirmButton->label(Button::State::Released).setFontSize(fontSize);
	_cancelButton->label(Button::State::Pressed).setFontSize(fontSize);
	_cancelButton->label(Button::State::Released).setFontSize(fontSize);
}

void HostGamePanel::_onGeometryChange()
{
	_updateGeometry();
	_updateFontSize();
}

void HostGamePanel::_onRender()
{

}

HostGamePanel::HostGamePanel(const std::string& p_name, spk::Widget* p_parent) :
	spk::Panel(p_name, p_parent),
	_confirmButton(makeChild<Button>("Confirm host game button", this)),
	_cancelButton(makeChild<Button>("Cancel host creation button", this)),
	_worldNameLabel(makeChild<TextLabel>("World name label", this)),
	_worldNameEntry(makeChild<TextEntry>("World name entry", this)),
	_chunkSizeLabel(makeChild<TextLabel>("Chunk size label", this)),
	_chunkSizeSelector(makeChild<ValueSelector<int>>("Chunk size selector", this))
{
	_worldNameLabel->label().setText("World name : ");
	_worldNameLabel->label().setVerticalAlignment(spk::VerticalAlignment::Centered);
	_worldNameLabel->label().setHorizontalAlignment(spk::HorizontalAlignment::Right);
	_worldNameLabel->box().setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_Cyan"));
	_worldNameLabel->activate();
	
	_worldNameEntry->setPlaceholder("Enter world name ...");
	_worldNameEntry->label().setVerticalAlignment(spk::VerticalAlignment::Centered);
	_worldNameEntry->label().setHorizontalAlignment(spk::HorizontalAlignment::Left);
	_worldNameEntry->box().setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_Cyan"));
	_worldNameEntry->activate();

	_chunkSizeLabel->label().setText("Chunk size : ");
	_chunkSizeLabel->label().setVerticalAlignment(spk::VerticalAlignment::Centered);
	_chunkSizeLabel->label().setHorizontalAlignment(spk::HorizontalAlignment::Right);
	_chunkSizeLabel->box().setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_Cyan"));
	_chunkSizeLabel->activate();

	_chunkSizeSelector->insertValue(8);
	_chunkSizeSelector->insertValue(16);
	_chunkSizeSelector->insertValue(32);
	_chunkSizeSelector->insertValue(64);
	_chunkSizeSelector->setIndex(0);
	_chunkSizeSelector->decrementValueButton()->box(Button::State::Pressed).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_DarkCyan"));
	_chunkSizeSelector->decrementValueButton()->box(Button::State::Released).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_Cyan"));
	_chunkSizeSelector->incrementValueButton()->box(Button::State::Pressed).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_DarkCyan"));
	_chunkSizeSelector->incrementValueButton()->box(Button::State::Released).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_Cyan"));
	_chunkSizeSelector->valueDisplayer()->box().setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_Cyan"));
	_chunkSizeSelector->activate();

	_confirmButton->setText("Confirm");
	_confirmButton->box(Button::State::Pressed).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_DarkCyan"));
	_confirmButton->box(Button::State::Released).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_Cyan"));
	_confirmButton->setOnClickCallback([&](){MainWidget::EventManager::instance()->notify_all(MainWidget::Event::ConfirmGameCreation);});
	_confirmButton->activate();

	_cancelButton->setText("Cancel");
	_cancelButton->box(Button::State::Pressed).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_DarkCyan"));
	_cancelButton->box(Button::State::Released).setSpriteSheet(TextureAtlas::instance()->spriteSheet("UI.Frame_Cyan"));
	_cancelButton->setOnClickCallback([&](){MainWidget::EventManager::instance()->notify_all(MainWidget::Event::EnterMainMenu);});
	_cancelButton->activate();
}