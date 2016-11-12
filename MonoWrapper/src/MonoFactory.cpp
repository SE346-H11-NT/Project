// This is the main DLL file.

#include "stdafx.h"

#include "MonoFactory.h"


MonoTexture* STDCALL MonoWrapper::MonoFactory::createMonoTexture(const char* str)
{
	return new MonoTexture(str);
}

void STDCALL MonoWrapper::MonoFactory::destroyMonoTexture(MonoTexture* instance)
{
	SAFE_DEL(instance);
}