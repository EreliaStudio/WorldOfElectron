#pragma once

#include "miscellaneous/texture_atlas.hpp"

#include "widget/panel/main_menu_panel.hpp"
#include "widget/panel/host_game_panel.hpp"
#include "widget/panel/join_game_panel.hpp"

class MainWidget : public spk::Widget
{
public:
	enum class Event
	{
		EnterMainMenu,
		EnterHostMenu,
		EnterJoinMenu,
		QuitGame,
		ConfirmGameCreation
	};

	using EventManager = spk::Singleton<spk::EventManager<Event>>;
	using Contract = spk::EventManager<Event>::Contract;

private:
	TextureAtlas::Instanciator _textureAtlasInstanciator;
	EventManager::Instanciator _eventManagerInstanciator;

	MainMenuPanel* _mainMenuPanel;
	std::unique_ptr<Contract> _mainMenuContract;

	HostGamePanel* _hostGamePanel;
	std::unique_ptr<Contract> _hostGameContract;

	JoinGamePanel* _joinGamePanel;
	std::unique_ptr<Contract> _joinGameContract;

	std::unique_ptr<Contract> _quitGameContract;
	
	void _onGeometryChange();

public:
	MainWidget(spk::Widget* p_parent);
	MainWidget(const std::string& p_name, spk::Widget* p_parent);
};