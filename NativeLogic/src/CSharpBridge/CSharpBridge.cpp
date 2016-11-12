#include "CSharpBridge.h"

#include <iostream>

extern "C"
{
	void __stdcall update(double deltaTime)
	{
		std::printf("Update called: %f", deltaTime);
	}
}