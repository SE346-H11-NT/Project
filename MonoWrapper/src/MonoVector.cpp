#include "Stdafx.h"
#include "MonoVector.h"
#include "MonoUtils.h"

namespace MonoWrapper
{
	namespace DataType
	{
		MONO_DEFINATION(MonoVector2, WindowsFramework::DataType::MVector2)
		MONO_DEFINATION(MonoVector3, WindowsFramework::DataType::MVector3)
		MONO_DEFINATION(MonoVector4, WindowsFramework::DataType::MVector4)

		MonoVector2::MonoVector2(float x, float y)
		{
			m_rawData = gcnew WindowsFramework::DataType::MVector2(x, y);
		}

		MonoVector3::MonoVector3(float x, float y, float z)
		{
			m_rawData = gcnew WindowsFramework::DataType::MVector3(x, y, z);
		}

		MonoWrapper::DataType::MonoVector3 MonoVector3::operator*(const MonoMatrix& mat)
		{
			return MonoVector3();
			//return (m_rawData->multiply(mat.getRawData()));
		}

		void MonoVector3::createVectorAndMultiplyToMatrix(float& x, float& y, float& z, const MonoMatrix& mat)
		{
			//gcroot<WindowsFramework::DataType::MVector3^> result = gcnew WindowsFramework::DataType::MVector3(x, y, z);
			//result = result->multiply(mat.getRawData());
			//x = result->getX();
			//y = result->getY();
			//z = result->getZ();
			//SAFE_DEL_ROOT(result);
		}

		MonoVector4::MonoVector4(float x, float y, float z, float w)
		{
			m_rawData = gcnew WindowsFramework::DataType::MVector4(x, y, z, w);
		}

	}
}