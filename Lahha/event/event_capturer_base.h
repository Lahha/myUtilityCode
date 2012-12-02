#ifndef LAHHA_EVENT_EVENTCAPTURER_BASE_H
#define LAHHA_EVENT_EVENTCAPTURER_BASE_H


#include <vector>
#include <boost/utility.hpp>
#include <boost/thread/mutex.hpp>

#include "event_handler.h"

namespace Event
{
	class EventCapturer;
};


class Event::EventCapturer : boost::noncopyable
{
	std::vector<EventHandler::sharedPtrType> handlers;
	boost::mutex _mutex;

protected:
	void _push(const Event& e);

public:
	EventCapturer();
	virtual ~EventCapturer();

	void linkHandler(EventHandler::sharedPtrType &handler);
	void unlinkHandler(EventHandler::sharedPtrType &handler);
};

#endif //LAHHA_EVENT_EVENTCAPTURER_GLFW_H