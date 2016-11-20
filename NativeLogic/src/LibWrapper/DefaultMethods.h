#ifndef __DEFAULT_METHODS_H__
#define __DEFAULT_METHODS_H__
#include <math.h>

// Wrapper header
#include "Generic/GenericDatatype.h"

// Math project header
#include "GraphicAlgorithms2D/MathDefaultConstant.h"

// Framework header
#include "DefaultStructure.h"
#include "DefaultConstant.h"

// STL
#include <vector>

using namespace std;

class Default
{
public:

	// -----------------------------------------------
	// Name: Default:checkIfBounded()
	// Desc: Check 2 passed Rectangle if it bounded each other.
	// -----------------------------------------------
	static bool checkIfBounded(const T6Rect* rect1, const T6Rect* rect2)
	{
		if ((rect2->right - rect1->left) < 0 || (rect1->right - rect2->left) < 0)
			return false;
		if ((rect2->top - rect1->bottom) < 0 || (rect1->top - rect2->bottom) < 0)
			return false;

		return true;
	}

	// -----------------------------------------------
	// Name: Default:checkIfBoundedNotEqual()
	// Desc: Check 2 passed Rectangle if it bounded each other.
	// 2 T6Rect JUST BOUND BY LINE ARE TREATED AS NOT BOUNDED
	// -----------------------------------------------
	static bool checkIfBoundedNotEqual(const T6Rect* rect1, const T6Rect* rect2)
	{
		if ((rect2->right - rect1->left) <= 0 || (rect1->right - rect2->left) <= 0)
			return false;
		if ((rect2->top - rect1->bottom) <= 0 || (rect1->top - rect2->bottom) <= 0)
			return false;

		return true;
	}


	// -----------------------------------------------
	// Name: Default:createRect()
	// Desc: Fast create a T6Rect follow passed variable.
	// -----------------------------------------------
	static T6Rect createT6Rect(long left, long right, long top, long bottom)
	{
		T6Rect result;

		result.left = left;
		result.right = right;
		result.top = top;
		result.bottom = bottom;

		return result;
	}


	// -----------------------------------------------
	// Name: Default:createRectFromCenter()
	// Desc: Fast create a T6Rect follow passed variable.
	// -----------------------------------------------
	static T6Rect createRectFromCenter(T6Vec3 position, Size frameSize)
	{
		return createRectFromDrawCenter(position, frameSize, DrawCenter::CENTER);
	}


	static T6Rect createRectFromDrawCenter(T6Vec3 position, Size frameSize, DrawCenter drawCenter)
	{
		T6Rect result;
		switch (drawCenter)
		{
		case TOPLEFT:
			result.left = (long)(position.x);
			result.top = (long)(position.y);
			result.right = (long)(position.x + frameSize.width);
			result.bottom = (long)(position.y - frameSize.height);
			break;
		case TOPRIGHT:
			result.left = (long)(position.x - frameSize.width);
			result.top = (long)(position.y);
			result.right = (long)(position.x);
			result.bottom = (long)(position.y - frameSize.height);
			break;
		case BOTTOMCENTER:
			result.left = (long)(position.x - frameSize.width / 2.0);
			result.top = (long)(position.y + frameSize.height);
			result.right = (long)(position.x + frameSize.width / 2.0);
			result.bottom = (long)(position.y);
			break;
		case CENTER:
			result.left = (long)(position.x - frameSize.width / 2.0);
			result.top = (long)(position.y + frameSize.height / 2.0);
			result.right = (long)(position.x + frameSize.width / 2.0);
			result.bottom = (long)(position.y - frameSize.height / 2.0);
			break;
		case BOTTOMLEFT:
			result.left = (long)(position.x);
			result.top = (long)(position.y + frameSize.height);
			result.right = (long)(position.x + frameSize.width);
			result.bottom = (long)(position.y);
			break;
		case BOTTOMRIGHT:
			result.left = (long)(position.x - frameSize.width);
			result.top = (long)(position.y + frameSize.height);
			result.right = (long)(position.x);
			result.bottom = (long)(position.y);
			break;
		case TOPCENTER:
			result.left = (long)(position.x - frameSize.width / 2.0);
			result.top = (long)(position.y);
			result.right = (long)(position.x + frameSize.width / 2.0);
			result.bottom = (long)(position.y - frameSize.height);
			break;
		default:
			break;
		}
		return result;
	}


	// -----------------------------------------------
	// Name: Default:createRectFromCenter()
	// Desc: Fast create a T6Rect follow passed variable.
	// -----------------------------------------------
	static T6Rect createRectFromBottomCenter(T6Vec3 position, Size frameSize)
	{
		T6Rect result;

		result.left = (long)(position.x - frameSize.width / 2);
		result.right = (long)(position.x + frameSize.width / 2);
		result.top = (long)(position.y + frameSize.height);
		result.bottom = (long)(position.y);

		return result;
	}


	// -----------------------------------------------
	// Name: Default:createRectFrom2Image()
	// Desc: Fast create a T6Rect with center at bottom frame1 and top frame2.
	// -----------------------------------------------
	static T6Rect createRectFrom2Image(T6Vec3 position, Size frameSize1, Size frameSize2)
	{
		T6Rect result;

		result.left = (long)(position.x - frameSize1.width / 2);
		result.right = (long)(position.x + frameSize1.width / 2);
		result.top = (long)(position.y + frameSize1.height / 2);
		result.bottom = (long)(position.y);

		return result;
	}


	// -----------------------------------------------
	// Name: Default<T>:tostr()
	// Desc: Convert the passed content to a string, char* or wchar_t* based on compiler setting.
	// -----------------------------------------------
	template <class T>
	static tstring tostr(const T& content)
	{
		tstringstream os;
		os << content;
		return os.str();
	}


	// -----------------------------------------------
	// Name: Default:createVector3()
	// Desc: Fast create a T6Vec3 by passed variables.
	// -----------------------------------------------
	static T6Vec3 createVector3(float x, float y, float z)
	{
		T6Vec3 result;

		result.x = x;
		result.y = y;
		result.z = z;

		return result;
	}


	// -----------------------------------------------
	// Name: Default:computeCenter()
	// Desc: Fast create a T6Vec3 for the center of the rect.
	// -----------------------------------------------
	static T6Vec3 computeCenter(T6Rect rect)
	{
		T6Vec3 result;

		result.x = (rect.left + rect.right) / 2.0F;
		result.y = (rect.top + rect.bottom) / 2.0F;
		result.z = DEFAULT_DEPTH;

		return result;
	}


	// -----------------------------------------------
	// Name: Default:checkIfPointInRect()
	// Desc: To check if the imported point is contained by the rect.
	// Base on Decard Axis.
	// -----------------------------------------------
	static bool checkIfPointInRect(T6Vec3 point, T6Rect rect)
	{
		bool inRangeX = (((point.x - rect.right) < 0) &&
			((point.x - rect.left) > 0));

		bool inRangeY = (((point.y - rect.top) < 0) &&
			((point.y - rect.bottom) > 0));

		return (inRangeX & inRangeY);
	}


	static T6Rect multipleRectWithDouble(T6Rect rect, double scaleValue)
	{
		double width = rect.right - rect.left;
		double height = rect.top - rect.bottom;
		width *= scaleValue;
		height *= scaleValue;
		width /= 2.0;
		height /= 2.0;

		T6Vec3 center = Default::computeCenter(rect);

		T6Rect result;
		result.left = (LONG)(center.x - width);
		result.right = (LONG)(center.x + width);
		result.top = (LONG)(center.y + height);
		result.bottom = (LONG)(center.y - height);

		return result;
	}


	static int fixAngle(int angle)
	{
		while (angle >= 360 || angle < 0)
		{
			if (angle >= 360)
				angle -= 360;
			else
				angle += 360;
		}

		return angle;
	}


	static double sin(double angleInRandian)
	{
		static double result[360];
#pragma region Initialize
		static bool isInitialized = false;

		if (!isInitialized)
		{
			FOR(360)
				result[i] = -2;
			isInitialized = !isInitialized;
		}
#pragma endregion

		int angle = Default::fixAngle((int)RADIAN_TO_DEGREE(angleInRandian));
		if (result[angle] < -1)
			result[angle] = std::sin(angleInRandian);

		return result[angle];
	}


	static double cos(double angleInRandian)
	{
		static double result[360];
#pragma region Initialize
		static bool isInitialized = false;

		if (!isInitialized)
		{
			FOR(360)
				result[i] = -2;
			isInitialized = !isInitialized;
		}
#pragma endregion

		int angle = Default::fixAngle((int)RADIAN_TO_DEGREE(angleInRandian));
		if (result[angle] < -1)
			result[angle] = std::cos(angleInRandian);

		return result[angle];
	}


	static double asin(double sinValue)
	{
		static double result[180];
#pragma region Initialize
		static bool isInitialized = false;

		if (!isInitialized)
		{
			FOR(180)
				result[i] = -2;
			isInitialized = !isInitialized;
		}
#pragma endregion

		int angle;
		FOR(180)
			if (result[i] == sinValue)
			{
				angle = i;
				goto RETURN;
			}

		angle = (int)RADIAN_TO_DEGREE(std::asin(sinValue));
		result[angle] = sinValue;

	RETURN:;
		return DEGREE_TO_RADIAN(angle);
	}

	// returning degree instead of radian
	static double acos(double cosValue)
	{
		static double result[180];
#pragma region Initialize
		static bool isInitialized = false;

		if (!isInitialized)
		{
			FOR(180)
				result[i] = -2;
			isInitialized = !isInitialized;
		}
#pragma endregion
		int angle;

		FOR(180)
			if (result[i] == cosValue)
			{
				angle = i;
				goto RETURN;
			}

		angle = (int)RADIAN_TO_DEGREE(std::acos(cosValue));
		result[angle] = cosValue;

	RETURN:;

		return angle;
	}


	static double computeDistance(T6Vec3 pos1, T6Vec3 pos2)
	{
		return std::sqrt(pow(pos1.x - pos2.x, 2.0) + pow(pos1.y - pos2.y, 2.0));
	}


	static double round(double value, double coefficient)
	{
		return coefficient * (int)(value / coefficient + 0.5);
	}


	template<class T>
	static void swap(T& a, T& b)
	{
		T c = a;
		a = b;
		b = c;
	}


	static T6Rect moveT6Rect(T6Rect& sourceT6Rect, T6Vec3 moveDistance)
	{
		sourceT6Rect.left += moveDistance.x;
		sourceT6Rect.right += moveDistance.x;
		sourceT6Rect.top += moveDistance.y;
		sourceT6Rect.bottom += moveDistance.y;

		return sourceT6Rect;
	}


	static vector<tstring> splitString(tstring source, char splitChar = '\n')
	{
		vector<tstring> result;
		int currentIndex = 0;
		FOR(source.length())
		{
			if (source[i] == splitChar)
			{
				result.push_back(tstring(source.substr(currentIndex, i)));
				currentIndex = i + 1;
			}
		}

		return result;
	}
};

#endif