#include "event_handler.h"

#include <boost\thread\locks.hpp>

using namespace Event;

EventHandler::EventHandler(void)
{	
}

EventHandler::EventHandler(const EventHandler& v)
{
	events = v.events;
	state = v.state;
}

EventHandler::~EventHandler(void)
{
	_mutex.lock();
	_mutex.unlock();
}

const ::Event::Event& EventHandler::_defEvent() const
{
	static const Event result(Event::NULL_EVENT);
	return result;
}

int EventHandler::count() const
{
	boost::lock_guard<boost::mutex> lock(_mutex);
	return events.size();
}

::Event::Event EventHandler::peek(unsigned i)
{
	boost::lock_guard<boost::mutex> lock(_mutex);
	
	if(i >= events.size())
		return _defEvent(); //throw std::range_error("Requested events out of range");

	auto it = events.begin();

	for(int i = 0; i <= i; i++)
		it++;

	return *it;
}

::Event::Event EventHandler::poll()
{
	boost::lock_guard<boost::mutex> lock(_mutex);

	if(events.size() == 0)
		return _defEvent();

	Event result = *events.begin();
	events.pop_front();

	return result;
}

void EventHandler::push(const ::Event::Event& e)
{
	boost::lock_guard<boost::mutex> lock(_mutex);
	events.push_back(e);
	state._event(e);
}

void EventHandler::flush()
{
	boost::lock_guard<boost::mutex> lock(_mutex);
	events.clear();
}

const InputState & EventHandler::getState() const
{
	return state;
}