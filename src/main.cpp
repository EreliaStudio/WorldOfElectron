#include "woe.hpp"

#include <chrono>

struct Context : public spk::Singleton<Context>
{
	spk::Client client;
	spk::Server server;
};

class ServerWidget : public spk::Widget
{
private:
	spk::Server& _server;

	std::unordered_map<spk::Message::Header::Type, std::function<void(const spk::Server::MessageObject&)>> _messageCallbacks;

	void _onUpdateEvent(const spk::UpdateEvent& p_event)
	{
		while (_server.messages().empty() == false)
		{
			spk::Server::MessageObject message = _server.messages().pop();

			if (_messageCallbacks.contains(message->header().type) == false)
			{
				throw std::runtime_error("Server callback not defined for ID [" + std::to_string(message->header().type) + "]");
			}

			_messageCallbacks[message->header().type](message);
		}
	}

public:
	ServerWidget(const std::wstring& p_name, spk::Server& p_server, const spk::SafePointer<Widget>& p_owner = nullptr) :
		spk::Widget(p_name, p_owner),
		_server(p_server)
	{
		setupMessageCallback(1, [&](const spk::Server::MessageObject& p_clientMessage){
			auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch()) .count();
			spk::cout << "Receiving a message from client at time [" << milliseconds << "]" << std::endl;
			_server.sendTo(p_clientMessage->header().emitterID, spk::Message(0));	
		});
	}

	void setupMessageCallback(const spk::Message::Header::Type& p_type, const std::function<void(const spk::Server::MessageObject&)>& p_callback)
	{
		if (_messageCallbacks.contains(p_type) == true)
		{
			throw std::runtime_error("Server callback already defined for ID [" + std::to_string(p_type) + "]");
		}
		_messageCallbacks[p_type] = p_callback;
	}
};

class ClientWidget : public spk::Widget
{
private:
	long long nextMessage = 0;

	spk::Client& _client;

	std::unordered_map<spk::Message::Header::Type, std::function<void(const spk::Client::MessageObject&)>> _messageCallbacks;

	void _onUpdateEvent(const spk::UpdateEvent& p_event)
	{
		while (_client.messages().empty() == false)
		{
			spk::Client::MessageObject message = _client.messages().pop();

			if (_messageCallbacks.contains(message->header().type) == false)
			{
				throw std::runtime_error("Server callback not defined for ID [" + std::to_string(message->header().type) + "]");
			}

			_messageCallbacks[message->header().type](message);
		}

		if (p_event.time >= nextMessage)
		{
			_client.send(spk::Message(1));

			nextMessage = p_event.time + std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)).count();
		}
	}

public:
	ClientWidget(const std::wstring& p_name, spk::Client& p_client, const spk::SafePointer<Widget>& p_owner = nullptr) :
		spk::Widget(p_name, p_owner),
		_client(p_client)
	{
		setupMessageCallback(0, [&](const spk::Server::MessageObject& p_clientMessage){
			auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) .count();

			spk::cout << "Receiving a message from server at time : " << milliseconds << std::endl;			
		});
	}

	void setupMessageCallback(const spk::Message::Header::Type& p_type, const std::function<void(const spk::Server::MessageObject&)>& p_callback)
	{
		if (_messageCallbacks.contains(p_type) == true)
		{
			throw std::runtime_error("Server callback already defined for ID [" + std::to_string(p_type) + "]");
		}
		_messageCallbacks[p_type] = p_callback;
	}
};

int main()
{
    spk::GraphicalApplication app;

    spk::SafePointer<spk::Window> win = app.createWindow(L"WorldOfElectron", spk::Geometry2D(0, 0, { 600, 600 }));
    win->setUpdateRate(0);

	Context::instanciate();

	Context::instance()->server.start(25500);
	Context::instance()->client.connect("127.0.0.1", 25500);

	ServerWidget serverWidget = ServerWidget(L"ServerWidget", Context::instance()->server, win->widget());
	serverWidget.activate();

	ClientWidget clientWidget = ClientWidget(L"ClientWidget", Context::instance()->client, win->widget());
	clientWidget.activate();

    return app.run();
}
