#include "T6_Keyboard.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

// -----------------------------------------------
// Name: T6_Keyboard:T6_Keyboard()
// Desc: Create an interface to get the keyboard status.
// -----------------------------------------------
T6_Keyboard::T6_Keyboard()
{
#if ENDABLE_CONTROLLER
	if (!createKeyboard())
		WARNING_BOX("Cannot start input device");
#endif
}


// -----------------------------------------------
// Name: T6_Keyboard:~T6_Keyboard()
// Desc: Release the interface after use (close game).
// -----------------------------------------------
T6_Keyboard::~T6_Keyboard()
{
}


// -----------------------------------------------
// Name: T6_Keyboard:createKeyboard()
// Desc: Create keyboard interface.
// -----------------------------------------------
bool T6_Keyboard::createKeyboard()
{
#if ENDABLE_CONTROLLER
#else
	return true;
#endif
}


// -----------------------------------------------
// Name: T6_Keyboard:update()
// Desc: Store the old keyboard status then get the new one.
// -----------------------------------------------
void T6_Keyboard::update()
{
#if ENDABLE_CONTROLLER
	memcpy(keyboardStatusPrevious_, keyboardStatus_, sizeof(keyboardStatus_));

	HRESULT result;
	int i = sizeof(keyboardStatus_);
	result = inputDevice_Keyboard_->GetDeviceState(sizeof(keyboardStatus_), (LPVOID)&keyboardStatus_);

	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			inputDevice_Keyboard_->Acquire();
		else
			WARNING_BOX("Cannot start input device");
	}
#endif
}


// -----------------------------------------------
// Name: T6_Keyboard:getKeyStatus()
// Desc: Check if the key is DOWN, UP, just PRESS or just RELEASE.
// -----------------------------------------------
KeyStatus T6_Keyboard::getKeyStatus(int key)
{
#if ENDABLE_CONTROLLER
	if (CHECK_IF_STATUS_IS_DOWN(keyboardStatus_[key])) {
		if (CHECK_IF_STATUS_IS_DOWN(keyboardStatusPrevious_[key]))
			return KeyStatus::KEY_DOWN;
		else
			return KeyStatus::KEY_PRESS;
	}
	else {
		if (CHECK_IF_STATUS_IS_DOWN(keyboardStatusPrevious_[key]))
			return KeyStatus::KEY_RELEASE;
		else
			return KeyStatus::KEY_UP;
	}
#else
	return KeyStatus::KEY_UP;
#endif
}