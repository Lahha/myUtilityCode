#include "event_capturer_base.h"

#include <algorithm>
#include <boost\thread\locks.hpp>

using namespace Event;

EventCapturer::EventCapturer()
{
}

EventCapturer::~EventCapturer()
{
}

void EventCapturer::_push(const ::Event::Event & e)
{
	boost::lock_guard<boost::mutex> lock(_mutex);
	std::for_each(handlers.begin(), handlers.end(), [&](EventHandler::sharedPtrType & h){ h->push(e); });
}

void EventCapturer::linkHandler(EventHandler::sharedPtrType &handler)
{
	boost::lock_guard<boost::mutex> lock(_mutex);
	if(handler == NULL)
		return;

	handlers.push_back(handler);
}

void EventCapturer::unlinkHandler(EventHandler::sharedPtrType &handler)
{
	boost::lock_guard<boost::mutex> lock(_mutex);
	auto i = std::find(handlers.begin(), handlers.end(), handler);
	
	if(i != handlers.end())
		handlers.erase(i);
}