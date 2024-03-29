#ifndef LAHHA_EVENT_INPUTCODES_H
#define LAHHA_EVENT_INPUTCODES_H


namespace Event
{

//glfw compatible
enum ENUM_KEY {
	KEY_UNKNOWN = 0,

	KEY_SPACE = 32,

	KEY_0 = 48,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9, //57
		
	KEY_A = 65,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z, //90

	KEY_SPECIAL = 256,
	
	KEY_ESCAPE,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_F13,
	KEY_F14,
	KEY_F15,
	KEY_F16,
	KEY_F17,
	KEY_F18,
	KEY_F19,
	KEY_F20,
	KEY_F21,
	KEY_F22,
	KEY_F23,
	KEY_F24,
	KEY_F25,

	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,

	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LCTRL,
	KEY_RCTRL,
	KEY_LALT,
	KEY_RALT, 

	KEY_TAB,
	KEY_ENTER,
	KEY_BACKSPACE,
	KEY_INSERT,
	KEY_DEL,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_HOME,
	KEY_END,

	KEY_KP_0,
	KEY_KP_1,
	KEY_KP_2,
	KEY_KP_3,
	KEY_KP_4,
	KEY_KP_5,
	KEY_KP_6,
	KEY_KP_7,
	KEY_KP_8,
	KEY_KP_9,
	KEY_KP_DIVIDE,
	KEY_KP_MULTIPLY,
	KEY_KP_SUBSTRACT,
	KEY_KP_ADD,
	KEY_KP_DECIMAL,
	KEY_KP_EQUAL,
	KEY_KP_ENTER,
	KEY_KP_NUMLOCK,
	
	KEY_CAPSLOCK,
	KEY_SCROLLLOCK,
	KEY_PAUSE,

	KEY_LAST //size for the state array
};

enum ENUM_MOUSE {
	MOUSE_LEFT = 0,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4, // for glfw compatibility
	MOUSE_5,
	MOUSE_6,
	MOUSE_7,
	MOUSE_8,
	MOUSE_LAST
};

};

#endif //LAHHA_EVENT_INPUTCODES_H