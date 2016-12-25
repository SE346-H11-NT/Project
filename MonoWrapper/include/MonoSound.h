#ifndef __MONO_SOUND__
#define __MONO_SOUND__

#include "DLLFlag.h"

#if defined(MONO_API_EXPORT)
#include <msclr/auto_gcroot.h>
using namespace System;
using namespace WindowsFramework::Media;
#endif

#include "MonoVector.h"
#include "MonoRectangle.h"

extern "C"
{
	namespace MonoWrapper {
		namespace Media
		{
			class MONOAPI MonoSound
			{
			public:
				void loadAudio(const char* path);
				void play(bool isLoop);
				void stop();

			private:
				const char* m_path;
				int m_ID;
			};
		}
	}
}
#endif //__MONO_SOUND__