#include "Stdafx.h"
#include "MonoMatrix.h"
#include "MonoUtils.h"

#define NativeMatrix WindowsFramework::DataType::MMatrix

namespace MonoWrapper
{
	namespace DataType
	{
		MonoMatrix::MonoMatrix()
		{
			m_ID = NativeMatrix::createMatrix();
		}

		MonoMatrix::MonoMatrix(const MonoMatrix& mat)
		{
			m_ID = NativeMatrix::createCopyMatrix(mat.m_ID);
		}

		MonoMatrix::MonoMatrix(int id)
		{
			m_ID = NativeMatrix::createCopyMatrix(id);
		}

		MonoMatrix::~MonoMatrix()
		{
			NativeMatrix::destroyMatrix(m_ID);
		}

		MonoMatrix MonoMatrix::operator*(const MonoMatrix& mat) const
		{
			return MonoMatrix();
			//return MonoMatrix(NativeMatrix::getFromStorage(m_ID)->multiply(mat.m_ID)->m_ID);
		}

		void MonoMatrix::scaling(MonoMatrix* outMat, float sx, float sy, float sz)
		{
			NativeMatrix::getFromStorage(outMat->m_ID)->scaling(sx, sy, sz);
		}

		void MonoMatrix::translation(MonoMatrix* outMat, float tx, float ty, float tz)
		{
			NativeMatrix::getFromStorage(outMat->m_ID)->translation(tx, ty, tz);
		}

		void MonoMatrix::indentity(MonoMatrix* outMat)
		{
			NativeMatrix::getFromStorage(outMat->m_ID)->identity();
		}

		int MonoMatrix::getID() const
		{
			return m_ID;
		}

		int MonoMatrix::operator=(const MonoMatrix& mat)
		{
			m_ID = NativeMatrix::createCopyMatrix(mat.m_ID);
			return m_ID;
		}

	}
}