#ifndef AutoAimingObject_h__
#define AutoAimingObject_h__

#include "Object.h"

#include "GraphicAlgorithms2D/CircleEquation.h"

class AutoAimingObject : virtual public Object
{
public:
	AutoAimingObject();
	virtual ~AutoAimingObject();
	int aim();
	void setAimingProperties(Object* target, double measure, T6Vec3 basePoint = POSITION_ZERO);
	virtual bool isTerminated() = 0;

protected:
	virtual void setBasicProperties();

protected:
	Object* target_;
	int currentAimingAngle_;
	double aimingMeasure_;
	T6Vec3 basePoint_;
};

#endif // AutoAimingObject_h__
