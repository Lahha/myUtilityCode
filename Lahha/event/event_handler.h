#ifndef LAHHA_EVENT_EVENTHANDLER_H
#define LAHHA_EVENT_EVENTHANDLER_H

#include <list>
#include <memory>
#include <boost\thread\mutex.hpp>

#include "event_inputcodes.h"
#include "event_event.h"
#include "event_input_state_buffer.h"

namespace Event
{
	class EventHandler;
};

class Event::EventHandler
{
public:
	typedef std::shared_ptr<EventHandler> sharedPtrType;

private:
	std::list<Event> events;
	InputState state;

	mutable boost::mutex _mutex;

	const Event& _defEvent() const;

public:
	EventHandler(void);
	EventHandler(const EventHandler& v);
	virtual ~EventHandler(void);

	int count() const;

	Event peek(unsigned i = 0);
	Event poll();

	void push(const Event& e);
	void flush();

	const InputState & getState() const;
};

#endif //LAHHA_EVENT_EVENTHANDLER_H