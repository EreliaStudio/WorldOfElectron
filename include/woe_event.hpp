#pragma once

#include "sparkle.hpp"

enum class Event
{
	NodeListEdited,
	CameraEdited
};

using EventNotifier = spk::Singleton<spk::EventNotifier<Event>>;