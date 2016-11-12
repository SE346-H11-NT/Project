#ifndef __MONO_TEXTURE__
#define __MONO_TEXTURE__

#include <msclr/auto_gcroot.h>
#include "MonoUtils.h"

using namespace System;
using namespace WindowsFramework::Graphic;

extern "C"
{
	namespace MonoWrapper {
		namespace Graphic
		{
			class MONOEXPORT MonoTexture
			{
			public:
				MonoTexture(const char* path);
				~MonoTexture();

				// TODO: merge param with T6Texture
				void draw();

			private:
				gcroot<MTexture^> m_texture;
				gcroot<System::String^> m_path;
			};
		}
	}
}
#endif //__MONO_TEXTURE__