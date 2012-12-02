#ifndef LAHHA_EVENT_H
#define LAHHA_EVENT_H

#include <Lahha/event/event_event.h>
#include <Lahha/event/event_input_state_buffer.h>
#include <Lahha/event/event_inputcodes.h>
#include <Lahha/event/event_handler.h>
#include <Lahha/event/event_capturer_base.h>
#include <Lahha/event/event_capturer_glfw.h>

//Link binaries for VC.
#ifdef _DEBUG
#pragma comment(lib, "event_d.lib")

#else
#pragma comment(lib, "event.lib")

#endif

#endif //LAHHA_EVENT_H