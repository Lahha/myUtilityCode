#include "event_input_state_buffer.h"

#include <cstring>

using namespace Event;

InputState::InputState(void)
{
	memset(keys, 0, sizeof(KeyValueType) * KEY_LAST);
}

InputState::InputState(const InputState& v)
{
	memcpy(keys, v.keys, sizeof(KeyValueType) * KEY_LAST);
}

InputState::~InputState(void) {}

void InputState::_event(const ::Event::Event &e)
{
	if(e.type == Event::KEY)
	{
		if(e.key.action == Event::BUTTON_PRESSED)
			setKey(e.key.key, 1);
		else if(e.key.action == Event::BUTTON_RELEASED)
			setKey(e.key.key, 0);
	}
}

void InputState::setKey(ENUM_KEY key, KeyValueType value) { keys[key] = value; }
InputState::KeyValueType InputState::getKey(ENUM_KEY key) const { return keys[key]; } 