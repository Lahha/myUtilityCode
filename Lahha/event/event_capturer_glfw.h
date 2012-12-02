#ifndef LAHHA_EVENT_EVENTCAPTURER_GLFW_H
#define LAHHA_EVENT_EVENTCAPTURER_GLFW_H

#include <GL/glfw.h>
#include <boost/thread/mutex.hpp>

#include "event_capturer_base.h"

namespace Event
{
	class glfwEventCapturer;
};

class Event::glfwEventCapturer : public EventCapturer
{
	static glfwEventCapturer * _instance;
	static boost::mutex _mutex;
	static void _allocateInstance();
	static void _deleteInstance();

	static void _glfwMousePosCallBack(int x, int y);
	static void _glfwMouseButtonCallBack(int button, int action);
	static void _glfwKeyCallBack(int key, int action);

	void _setCallBacks();

public:
	glfwEventCapturer();
	virtual ~glfwEventCapturer();

	static glfwEventCapturer & getInstance();
};

#endif //LAHHA_EVENT_EVENTCAPTURER_GLFW_H