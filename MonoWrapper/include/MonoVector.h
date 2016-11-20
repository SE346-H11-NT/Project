#ifndef __MONOVECTOR3__
#define __MONOVECTOR3__

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
			class MONOAPI MonoVector2
			{
				MONO_DECLARE(MonoVector2, WindowsFramework::DataType::MVector2)
			public:
				MonoVector2(float x, float y);
			};

			class MONOAPI MonoVector3
			{
				MONO_DECLARE(MonoVector3, WindowsFramework::DataType::MVector3)
			public:
				MonoVector3(float x, float y, float z);
				MonoVector3 operator*(const MonoMatrix& mat);
				static void createVectorAndMultiplyToMatrix(float& x, float& y, float& z, const MonoMatrix& mat);
			};

			class MONOAPI MonoVector4
			{
				MONO_DECLARE(MonoVector4, WindowsFramework::DataType::MVector4)
			public:
				MonoVector4(float x, float y, float z, float w);
			};
}
	}
}

#endif //__MONOVECTOR3__