#include "Stdafx.h"
#include "MonoMatrix.h"
#include "MonoUtils.h"

namespace MonoWrapper
{
	namespace DataType
	{
		MonoMatrix::MonoMatrix()
		{
			m_matrix = gcnew WindowsFramework::DataType::MMatrix();
		}
		
		MonoMatrix::MonoMatrix(const gcroot<WindowsFramework::DataType::MMatrix^>& mat)
		{
			m_matrix = gcnew WindowsFramework::DataType::MMatrix(mat);
		}

		MonoMatrix::~MonoMatrix()
		{
			SAFE_DEL_ROOT(m_matrix);
		}

		MonoMatrix MonoMatrix::operator*(const MonoMatrix& mat) const
		{
			return m_matrix->multiply(mat.m_matrix);
		}

		gcroot<WindowsFramework::DataType::MMatrix^> MonoMatrix::getRawData() const
		{
			return m_matrix;
		}

		void MonoMatrix::scaling(MonoMatrix* outMat, float sx, float sy, float sz)
		{
			outMat->m_matrix->scaling(sx, sy, sz);
		}

		void MonoMatrix::translation(MonoMatrix* outMat, float tx, float ty, float tz)
		{
			outMat->m_matrix->translation(tx, ty, tz);
		}

		void MonoMatrix::indentity(MonoMatrix* outMat)
		{
			outMat->m_matrix->identity();
		}

	}
}