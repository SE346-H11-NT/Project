#ifndef __MONOMATRIX__
#define __MONOMATRIX__

#include "DLLFlag.h"

#if defined(MONO_API_EXPORT)
#include <msclr/auto_gcroot.h>
using namespace WindowsFramework::DataType;
#endif

extern "C"
{
	namespace MonoWrapper
	{
		namespace DataType
		{
			class MONOAPI MonoMatrix
			{
			public:
				MonoMatrix();
				~MonoMatrix();

				MonoMatrix operator*(const MonoMatrix& mat) const;
				static void scaling(MonoMatrix* outMat, float sx, float sy, float sz);
				static void translation(MonoMatrix* outMat, float tx, float ty, float tz);
				static void indentity(MonoMatrix* outMat);

#if defined(MONO_API_EXPORT)
			public:
				MonoMatrix(const gcroot<WindowsFramework::DataType::MMatrix^>& mat);
				gcroot<WindowsFramework::DataType::MMatrix^> getRawData() const;

			private:
				gcroot<WindowsFramework::DataType::MMatrix^>	m_matrix;
#endif
			};
}
	}
}

#endif //__MONOMATRIX__