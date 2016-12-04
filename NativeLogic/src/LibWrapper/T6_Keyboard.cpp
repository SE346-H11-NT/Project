#include "T6_Keyboard.h"
#include "CSharpBridge/DLLImporter.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

// -----------------------------------------------
// Name: T6_Keyboard:T6_Keyboard()
// Desc: Create an interface to get the keyboard status.
// -----------------------------------------------
T6_Keyboard::T6_Keyboard()
{
}


// -----------------------------------------------
// Name: T6_Keyboard:~T6_Keyboard()
// Desc: Release the interface after use (close game).
// -----------------------------------------------
T6_Keyboard::~T6_Keyboard()
{
}


// -----------------------------------------------
// Name: T6_Keyboard:update()
// Desc: Store the old keyboard status then get the new one.
// -----------------------------------------------
void T6_Keyboard::update()
{
#if ENDABLE_CONTROLLER
	WrappedKeyboard::getInstance()->update();
#endif
}


// -----------------------------------------------
// Name: T6_Keyboard:getKeyStatus()
// Desc: Check if the key is DOWN, UP, just PRESS or just RELEASE.
// -----------------------------------------------
KeyStatus T6_Keyboard::getKeyStatus(int key)
{
#if ENDABLE_CONTROLLER
	if (WrappedKeyboard::getInstance()->isKeyDown(key)) {
		if (WrappedKeyboard::getInstance()->isKeyPreviouslyDown(key))
			return KeyStatus::KEY_DOWN;
		else
			return KeyStatus::KEY_PRESS;
	}
	else {
		if (WrappedKeyboard::getInstance()->isKeyPreviouslyDown(key))
			return KeyStatus::KEY_RELEASE;
		else
			return KeyStatus::KEY_UP;
	}
#else
	return KeyStatus::KEY_UP;
#endif
}