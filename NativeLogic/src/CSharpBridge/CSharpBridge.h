#ifndef __CSHARP_BRIDGE__
#define __CSHARP_BRIDGE__

#include "BridgeUtils.h"

extern "C"
{
	CBEXPORT void STDCALL nativeInitialize();
	CBEXPORT void STDCALL nativeRelease();
	CBEXPORT void STDCALL nativeUpdate(double deltaTime);
	CBEXPORT void STDCALL nativeDraw();
}

#endif //__CSHARP_BRIDGE__