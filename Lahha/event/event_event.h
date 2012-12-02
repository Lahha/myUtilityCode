#ifndef LAHHA_EVENT_EVENT_H
#define LAHHA_EVENT_EVENT_H

#include "event_inputcodes.h"

namespace Event
{
	struct Event;
};

struct Event::Event
{
	enum EventType {
		NULL_EVENT = 0,

		MOUSE_BUTTON,
		MOUSE_POS,
		KEY,
	} type;

	enum ENUM_ACTION {
		ACTION_UNKNOWN = 0,
		BUTTON_PRESSED = 1,
		BUTTON_RELEASED,
	};

	union
	{
		struct
		{
			ENUM_ACTION action;
			ENUM_MOUSE button;
		} mouseButton;

		struct
		{
			int x, y;
		} mousePos;

		struct
		{
			ENUM_ACTION action;
			ENUM_KEY key;
		} key;
	};

	Event(EventType et = NULL_EVENT) { type = et; }
};

#endif //LAHHA_EVENT_EVENTHANDLER_H