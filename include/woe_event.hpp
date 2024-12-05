#pragma once

#include "sparkle.hpp"

enum class Event
{
	EnterMainMenuScreen
};

using EventNotifier = spk::Singleton<spk::EventNotifier<Event>>;