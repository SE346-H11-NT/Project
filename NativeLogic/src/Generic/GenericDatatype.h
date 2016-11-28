#ifndef __GENERIC_DATA_TYPE__
#define __GENERIC_DATA_TYPE__

#include "CSharpBridge/DLLImporter.h"

#define USE_SELF_DEFINING_CLASSES	0

#define VECTOR_TYPE	1

#if VECTOR_TYPE == 0	// int
#define VECTOR_MEMBER_TYPE	int
#define VECTOR_VALUE_ABS	abs
#elif VECTOR_TYPE == 1 // float
#define VECTOR_MEMBER_TYPE	float
#define VECTOR_VALUE_ABS	fabs
#endif

#if USE_SELF_DEFINING_CLASSES
template <unsigned int VectorSize>
struct T6Vector
{
	float	m_rawData[VectorSize];

	unsigned int getSize()
	{
		return VectorSize;
	}

	T6Vector<VectorSize>	setZero()
	{
		memset(m_rawData, 0, sizeof(m_rawData));
		return *this;
	}

	const bool operator!=(const T6Vector<VectorSize>& otherVec) const
	{
		for (int i = 0; i < VectorSize; ++i)
		{
			if (m_rawData[i] != otherVec.m_rawData[i])
			{
				return true;
			}
		}

		return false;
	}

	T6Vector<VectorSize> operator*(const float& scale) const
	{
		T6Vector<VectorSize>	result;
		for (int i = 0; i < VectorSize; ++i)
		{
			result.m_rawData[i] = m_rawData[i] * scale;
		}
	}
};

union T6Vec4
{
	T6Vector<4u>	m_vector;

	T6Vec4(float fx = 0.0f, float fy = 0.0f, float fz = 0.0f, float fw = 0.0f)
	{
		x = fx;
		y = fy;
		z = fz;
	}

	T6Vec4(const unsigned int& hexcode)
	{
		*this = hexcode;
	}

	~T6Vec4(){}

	struct
	{
		float x, y, z, w;
	};

	struct
	{
		float a, r, g, b;
	};

	const bool operator!=(const T6Vec4& otherVec) const
	{
		return m_vector != otherVec.m_vector;
	}

	const T6Vec4& operator=(const unsigned int& hexcode)
	{
		a = (hexcode >> 24) & 0xff;
		r = (hexcode >> 16) & 0xff;
		g = (hexcode >> 8) & 0xff;
		b = (hexcode >> 0) & 0xff;
	}
};

union T6Vec3
{
	T6Vector<3u>	m_vector;

	T6Vec3(float fx = 0.0f, float fy = 0.0f, float fz = 0.0f)
	{
		x = fx;
		y = fy;
		z = fz;
	}

	T6Vec3(const T6Vector<3u>& vector)
	{
		m_vector = vector;
	}

	~T6Vec3(){}

	struct
	{
		float x, y, z;
	};

	struct
	{
		float r, g, b;
	};

	const bool operator!=(const T6Vec3& otherVec) const
	{
		return m_vector != otherVec.m_vector;
	}

	const bool operator==(const T6Vec3& otherVec) const
	{
		return !(m_vector != otherVec.m_vector);
	}

	T6Vec3 operator*(const float& scale) const
	{
		return m_vector * scale;
	}
};

union T6Vec2
{
	T6Vector<2u>	m_vector;

	T6Vec2(float fx = 0.0f, float fy = 0.0f)
	{
		x = fx;
		y = fy;
	}

	T6Vec2(const T6Vec3& otherVec)
	{
		x = otherVec.x;
		y = otherVec.y;
	}

	~T6Vec2(){}

	const bool operator!=(const T6Vec2& otherVec) const
	{
		return m_vector != otherVec.m_vector;
	}

	struct
	{
		float x, y;
	};

	struct
	{
		float u, v;
	};
};

typedef T6Vec4 T6Color;

template <unsigned int MatrixSize>
struct T6Matrix
{
	float	m_rawData[MatrixSize * MatrixSize];

	static const int COMPONENT_COUNT = MatrixSize * MatrixSize;
	static const int MATRIX_SIZE = MatrixSize;

	T6Matrix<MatrixSize>	setZero()
	{
		memset(m_rawData, 0, sizeof(m_rawData));
		return *this;
	}

	T6Matrix<MatrixSize>	indentity()
	{
		setZero();
		for (int i = 0; i < COMPONENT_COUNT; i += (MATRIX_SIZE + 1))
		{
			m_rawData[i] = 1.0f;
		}
	}
};

union T6Matrix4
{
	T6Matrix<4u>	m_matrix;

	T6Matrix4(){
		m_matrix.setZero();
	}
};

#else
struct T6Rect
{
	int left, top, right, bottom;

	WrappedRect	getNativeRect()
	{
		return WrappedRect(left, top, right, bottom);
	}

	int getID()
	{
		return WrappedRect(left, top, right, bottom).getID();
	}
};

template <unsigned int VectorSize>
struct T6Vector
{
	VECTOR_MEMBER_TYPE	m_rawData[VectorSize];

	unsigned int getSize()
	{
		return VectorSize;
	}

	T6Vector<VectorSize>	setZero()
	{
		memset(m_rawData, 0, sizeof(m_rawData));
		return *this;
	}

	const bool operator!=(const T6Vector<VectorSize>& otherVec) const
	{
		return !(*this == otherVec);
	}

	const bool operator==(const T6Vector<VectorSize>& otherVec) const
	{
		for (int i = 0; i < VectorSize; ++i)
		{
			if (m_rawData[i] != otherVec.m_rawData[i])
			{
				return false;
			}
		}

		return true;
	}

	T6Vector<VectorSize> operator*(const float& scale) const
	{
		T6Vector<VectorSize>	result;
		for (int i = 0; i < VectorSize; ++i)
		{
			result.m_rawData[i] = m_rawData[i] * scale;
		}
	}
};

struct T6Vec2
{
	union
	{
		T6Vector<2u>	m_vector;

		struct {
			VECTOR_MEMBER_TYPE x, y;
		};

		struct {
			VECTOR_MEMBER_TYPE u, v;
		};
	};

	T6Vec2(int ix = 0, int iy = 0)
		: x(ix)
		, y(iy)
	{
	}

	T6Vec2 getInvert() const
	{
		return T6Vec2(-x, -y);
	}

	WrappedVec2	getNativeVector()
	{
		return WrappedVec2(x, y);
	}

	int getID()
	{
		return WrappedVec2(x, y).getID();
	}
};


struct T6Vec3
{
	union
	{
		T6Vector<3u>	m_vector;

		struct {
			VECTOR_MEMBER_TYPE x, y, z;
		};

		struct {
			VECTOR_MEMBER_TYPE r, g, b;
		};
	};

	T6Vec3(VECTOR_MEMBER_TYPE ix = 0,
		VECTOR_MEMBER_TYPE iy = 0, 
		VECTOR_MEMBER_TYPE iz = 0)
		: x(ix)
		, y(iy)
		, z(iz)
	{
	}

	T6Vec3 operator + (const T6Vec3& vec) const
	{
		T6Vec3 result;
		result.x = x + vec.x;
		result.y = y + vec.y;
		result.z = z + vec.z;
		return result;
	}

	T6Vec3 operator += (const T6Vec3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	T6Vec3 operator - (const T6Vec3& vec) const
	{
		T6Vec3 result;
		result.x = x - vec.x;
		result.y = y - vec.y;
		result.z = z - vec.z;
		return result;
	}

	T6Vec3 operator * (const double& scale) const
	{
		T6Vec3 result;
		result.x = x * scale;
		result.y = y * scale;
		result.z = z * scale;
		return result;
	}

	T6Vec3 operator /= (const double& scale)
	{
		x /= scale;
		y /= scale;
		z /= scale;
		return *this;
	}

	T6Vec3 operator * (const WrappedMatrix& mat) const
	{
		T6Vec3 result(x, y, z);
		WrappedVec3::createVectorAndMultiplyToMatrix(result.x, result.y, result.z, mat);
		return result;
	}

	int operator *= (const WrappedMatrix& mat)
	{
		WrappedVec3::createVectorAndMultiplyToMatrix(x, y, z, mat);
		return this->getID();
	}

	bool operator== (const T6Vec3& vec) const
	{
		return (this->m_vector == vec.m_vector);
	}

	bool operator!= (const T6Vec3& vec) const
	{
		return (this->m_vector != vec.m_vector);
	}

	T6Vec3 getInvert() const
	{
		return T6Vec3(-x, -y, -z);
	}

	WrappedVec3	getNativeVector()
	{
		return WrappedVec3(x, y, z);
	}

	int getID()
	{
		return WrappedVec3(x, y, z).getID();
	}
};

struct T6Vec4
{
	union
	{
		T6Vector<4u>	m_vector;

		struct {
			VECTOR_MEMBER_TYPE x, y, z, w;
		};

		struct {
			VECTOR_MEMBER_TYPE r, g, b, a;
		};
	};

	T6Vec4(VECTOR_MEMBER_TYPE ix, 
		VECTOR_MEMBER_TYPE iy, 
		VECTOR_MEMBER_TYPE iz = 0, 
		VECTOR_MEMBER_TYPE iw = 0)
		: x(ix)
		, y(iy)
		, z(iz)
		, w(iw)
	{
	}

	T6Vec4(int hexCode = 0)
		: a((hexCode >> 24) & 0xff)
		, r((hexCode >> 16) & 0xff)
		, g((hexCode >>  8) & 0xff)
		, b((hexCode >>  0) & 0xff)
	{
	}

	WrappedVec4	getNativeVector()
	{
		return WrappedVec4(x, y, z, w);
	}

	int getID()
	{
		return WrappedVec4(x, y, z, w).getID();
	}
};

typedef	WrappedMatrix	T6Matrix4;
typedef T6Vec4			T6Color;
#endif
#endif // __GENERIC_DATA_TYPE__