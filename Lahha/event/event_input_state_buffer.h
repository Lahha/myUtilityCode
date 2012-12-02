#ifndef LAHHA_EVENT_INPUTSTATEBUFFER_H
#define LAHHA_EVENT_INPUTSTATEBUFFER_H

#include <memory>

#include "event_inputcodes.h"
#include "event_event.h"

namespace Event
{
	class InputState;
};

class Event::InputState
{
public:
	typedef std::shared_ptr<InputState> SharedPtrType;
	typedef unsigned char KeyValueType;

protected:
	KeyValueType keys[KEY_LAST];

	friend class EventHandler;
	void _event(const Event &e);

public:
	InputState(void);
	InputState(const InputState& v);
	virtual ~InputState(void);

	void setKey(ENUM_KEY key, KeyValueType value);
	KeyValueType getKey(ENUM_KEY key) const;
};

#endif //LAHHA_EVENT_INPUTSTATEBUFFER_H