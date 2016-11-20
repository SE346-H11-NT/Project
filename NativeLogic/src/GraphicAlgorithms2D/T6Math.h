#ifndef __T6_MATH_H__
#define __T6_MATH_H__

#include "CircleEquation.h"

class T6_Math
{
public:

	// -----------------------------------
	// Name: T6_Math::caculate2PointDistanceXY()
	// Desc: Caculating the distance between 2 point.
	// -----------------------------------
	static double caculate2PointDistanceXY(T6Vec3 point1, T6Vec3 point2)
	{
		T6Vec3 distanceVector;
		distanceVector.x = pow(point1.x - point2.x, 2);
		distanceVector.y = pow(point1.y - point2.y, 2);

		return sqrt(distanceVector.x + distanceVector.y);
	}



	// -----------------------------------
	// Name: T6_Math::caculateLineAngle()
	// Desc: Caculating the angle between a line through 2 point with [y = 0] line.
	// Point 1 is the base.
	// Return value in Radian.
	// -----------------------------------
	static double caculateLineAngle(T6Vec3 point1, T6Vec3 point2)
	{
		return
			CircleEquation(point1, point2).getDegreeFromCoodirate(point2);
	}
};

#endif