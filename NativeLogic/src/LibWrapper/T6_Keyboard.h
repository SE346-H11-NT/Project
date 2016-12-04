//==============================
// Last change: 26/9/2014
// T6_Framework
// T6_Keyboard v1.0
// This is the class allow you to connect to your keyboard and get it's status.
//==============================
#ifndef __INPUT_H__
#define __INPUT_H__

#include <dinput.h>

#include "DefaultConstant.h"

#define CHECK_IF_STATUS_IS_DOWN(status) (status & 0x80)

enum KeyStatus
{
	KEY_DOWN = 0,
	KEY_PRESS,
	KEY_RELEASE,
	KEY_UP,
	NUM_OF_KEY_STATUS
};

class T6_Keyboard
{
public:
	T6_Keyboard();
	~T6_Keyboard();

	void update();
	KeyStatus getKeyStatus(int key);

private:
	bool createKeyboard();
};

#endif