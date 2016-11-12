// MonoWrapper.h

#pragma once
#include "MonoUtils.h"
#include "MonoTexture.h"

using namespace System;

using namespace MonoWrapper::Graphic;

extern "C"
{
	namespace MonoWrapper {

		class MONOEXPORT MonoFactory
		{
		public:
			static MonoTexture* STDCALL createMonoTexture(const char* str);
			static void STDCALL destroyMonoTexture(MonoTexture* instance);
		};
	}
}
