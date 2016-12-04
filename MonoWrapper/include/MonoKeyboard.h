#ifndef __MONOKEYBOARD__
#define __MONOKEYBOARD__

#include "DLLFlag.h"

#if defined(MONO_API_EXPORT)
#include <msclr/auto_gcroot.h>
using namespace System;
using namespace WindowsFramework::Graphic;
#endif

extern "C"
{
	namespace MonoWrapper {
		namespace Controller
		{
			class MONOAPI MonoKeyboard
			{
			public:
				static MonoKeyboard* getInstance();

				bool isKeyDown(int keyCode);
				bool isKeyPreviouslyDown(int keyCode);

				void update();

			private:
				MonoKeyboard();
				~MonoKeyboard();

				static MonoKeyboard* m_instance;
			};
		}
	}
}
#endif //__MONOKEYBOARD__