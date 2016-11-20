#ifndef __MONOT6RectANGLE__
#define __MONOT6RectANGLE__

#include "DLLFlag.h"

#if defined(MONO_API_EXPORT)
#include <msclr/auto_gcroot.h>
using namespace WindowsFramework::DataType;
#endif

#include "MonoMatrix.h"

extern "C"
{
	namespace MonoWrapper
	{
		namespace DataType
		{
			class MONOAPI MonoRectangle
			{
				MONO_DECLARE(MonoRectangle, WindowsFramework::DataType::MRectangle)
			public:
				MonoRectangle(int left, int top, int right, int bottom);
			};
		}
	}
}

#endif //__MONOT6RectANGLE__