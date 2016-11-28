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
			m_ID = NativeVec2::create(x, y);
		}

		MonoVector3::MonoVector3(float x, float y, float z)
		{
			m_ID = NativeVec3::create(x, y, z);
		}

		MonoWrapper::DataType::MonoVector3 MonoVector3::operator*(const MonoMatrix& mat)
		{
			return MonoVector3();
			//return (m_rawData->multiply(mat.getRawData()));
		}

		void MonoVector3::createVectorAndMultiplyToMatrix(float& x, float& y, float& z, const MonoMatrix& mat)
		{
			int holdingID = NativeVec3::create(x, y, z);
			int resultID = NativeVec3::getFromStorage(holdingID)->multiply(mat.getID());
			x = NativeVec3::getFromStorage(resultID)->getX();
			y = NativeVec3::getFromStorage(resultID)->getY();
			z = NativeVec3::getFromStorage(resultID)->getZ();
			NativeVec3::destroy(holdingID);
			NativeVec3::destroy(resultID);
		}

		MonoVector4::MonoVector4(float x, float y, float z, float w)
		{
			m_ID = WindowsFramework::DataType::MVector4::create(x, y, z, w);
		}

	}
}