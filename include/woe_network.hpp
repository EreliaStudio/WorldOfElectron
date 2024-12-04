#pragma once

#include "sparkle.hpp"

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
	}

public:
	ClientWidget(const std::wstring& p_name, spk::Client& p_client, const spk::SafePointer<Widget>& p_owner = nullptr) :
		spk::Widget(p_name, p_owner),
		_client(p_client)
	{

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
