#include "widget/main_widget.hpp"

void MainWidget::_onGeometryChange()
{
	_mainMenuPanel->setGeometry(0, size());
	_hostGamePanel->setGeometry(0, size());
	_joinGamePanel->setGeometry(0, size());
}

MainWidget::MainWidget(spk::Widget* p_parent) :
	MainWidget("Anonymous MainWidget", p_parent)
{
	
}

MainWidget::MainWidget(const std::string& p_name, spk::Widget* p_parent) :
	spk::Widget(p_name, p_parent),
	_textureAtlasInstanciator(),
	_eventManagerInstanciator(),
	_mainMenuPanel(makeChild<MainMenuPanel>("MainMenuPanel", this)),
	_hostGamePanel(makeChild<HostGamePanel>("HostGamePanel", this)),
	_joinGamePanel(makeChild<JoinGamePanel>("JoinGamePanel", this))
{
	_mainMenuContract = EventManager::instance()->subscribe(Event::EnterMainMenu, [&](){
		_mainMenuPanel->activate();
	});
	
	_joinGameContract = EventManager::instance()->subscribe(Event::EnterJoinMenu, [&](){
		_joinGamePanel->activate();
	});
	
	_hostGameContract = EventManager::instance()->subscribe(Event::EnterHostMenu, [&](){
		_hostGamePanel->activate();
	});
	
	_quitGameContract = EventManager::instance()->subscribe(Event::QuitGame, [&](){
		spk::Application::activeApplication()->quit(0);
	});

	EventManager::instance()->notify_all(Event::EnterMainMenu);
}