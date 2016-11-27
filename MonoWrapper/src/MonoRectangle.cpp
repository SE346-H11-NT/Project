#include "Stdafx.h"
#include "MonoRectangle.h"
#include "MonoUtils.h"
namespace MonoWrapper
{
	namespace DataType
	{
		MONO_DEFINATION(MonoRectangle, WindowsFramework::DataType::MRectangle)

		MonoRectangle::MonoRectangle(int left, int top, int right, int bottom)
		{
			m_ID = WindowsFramework::DataType::MRectangle::create(left, top, right, bottom);
		}
	}
}