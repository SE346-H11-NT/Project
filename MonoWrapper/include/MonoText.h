#ifndef __MONO_TEXT__
#define __MONO_TEXT__

#include "DLLFlag.h"

#if defined(MONO_API_EXPORT)
#include <msclr/auto_gcroot.h>
using namespace System;
using namespace WindowsFramework::Graphic;
#endif

#include "MonoVector.h"

extern "C"
{
	namespace MonoWrapper {
		namespace Graphic
		{
			class MONOAPI MonoText
			{
			public:
				//void drawText(const T& Content, T6Vec3 Position, T6Color Color = DEFAULT_FONT_COLOR,
				//	int Size = DEFAULT_FONTSIZE, UINT DT_Type = DT_LEFT, bool converted = true)
				static void drawText(const char* Content, int Position,
					int Color, int Size, int DT_Type);
			};
}
	}
}
#endif //__MONO_TEXT__