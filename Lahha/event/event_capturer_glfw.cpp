#include "event_capturer_glfw.h"

#include <boost\thread\locks.hpp>

using namespace Event;

glfwEventCapturer::glfwEventCapturer()
{
	if(_instance)
		throw std::runtime_error("Tried to create illegitimate instance of glfwEventCapturer. Use glfwEventCapturer::getInstance() instead.");
}

glfwEventCapturer::~glfwEventCapturer()
{
}

glfwEventCapturer * glfwEventCapturer::_instance = NULL;
boost::mutex glfwEventCapturer::_mutex;

void glfwEventCapturer::_allocateInstance()
{
	boost::lock_guard<boost::mutex> lock(_mutex);
	if(!_instance)
		_instance = new glfwEventCapturer;

	_instance->_setCallBacks(); //Have to do it here instead of constructor due glfw calling the callbacks instantly and causing race and deadlocks the mutex.
}

void glfwEventCapturer::_deleteInstance()
{
	boost::lock_guard<boost::mutex> lock(_mutex);
	if(_instance)
		delete _instance;
	_instance = NULL;
}

void glfwEventCapturer::_setCallBacks()
{
	glfwSetMousePosCallback(_glfwMousePosCallBack);
	glfwSetMouseButtonCallback(_glfwMouseButtonCallBack);
	glfwSetKeyCallback(_glfwKeyCallBack);
}

void glfwEventCapturer::_glfwMousePosCallBack(int x, int y)
{
	Event e(Event::MOUSE_POS);

	e.mousePos.x = x;
	e.mousePos.y = y;

	getInstance()._push(e);
}

void glfwEventCapturer::_glfwMouseButtonCallBack(int button, int action)
{
	Event e(Event::MOUSE_BUTTON);

	switch(button)
	{
	case GLFW_MOUSE_BUTTON_LEFT: 
		e.mouseButton.button = MOUSE_LEFT; break;
	case GLFW_MOUSE_BUTTON_RIGHT: 
		e.mouseButton.button = MOUSE_RIGHT; break;
	case GLFW_MOUSE_BUTTON_MIDDLE: 
		e.mouseButton.button = MOUSE_MIDDLE; break;
	default: 
		e.mouseButton.button = MOUSE_8; break;
	}

	switch(action)
	{
	case GLFW_PRESS:
		e.mouseButton.action = Event::BUTTON_PRESSED; break;
	case GLFW_RELEASE:
		e.mouseButton.action = Event::BUTTON_RELEASED; break;
	default:
		e.mouseButton.action = Event::ACTION_UNKNOWN; break;
	}

	getInstance()._push(e);
}

void glfwEventCapturer::_glfwKeyCallBack(int key, int action)
{
	Event e(Event::KEY);

	e.key.key = ENUM_KEY(key); 

	switch(action)
	{
	case GLFW_PRESS:
		e.key.action = Event::BUTTON_PRESSED; break;
	case GLFW_RELEASE:
		e.key.action = Event::BUTTON_RELEASED; break;
	default:
		e.key.action = Event::ACTION_UNKNOWN; break;
	}

	getInstance()._push(e);
}

glfwEventCapturer & glfwEventCapturer::getInstance()
{
	if(!_instance)
		_allocateInstance();

	return *_instance;
}