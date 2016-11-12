#include "CSharpBridge.h"

#include <iostream>

#include "../GameLogic/GameMain.h"
extern "C"
{
	CBEXPORT void STDCALL nativeInitialize()
	{
		GameMain::initialize();
	}

	CBEXPORT void STDCALL nativeRelease()
	{
		GameMain::release();
	}

	CBEXPORT void STDCALL nativeUpdate(double deltaTime)
	{
		GameMain::getInstance()->update(deltaTime);
	}

	CBEXPORT void STDCALL nativeDraw()
	{
		GameMain::getInstance()->draw();
	}
}