#include "AutoAimingObject.h"


AutoAimingObject::AutoAimingObject()
{
}


AutoAimingObject::~AutoAimingObject()
{
}

int AutoAimingObject::aim()
{
	T6Vec3 base = basePoint_;
	if (base == POSITION_ZERO)
		base = position_;

	T6Vec3 aimPoint = Default::computeCenter(target_->getRect());

	currentAimingAngle_ = (int)CircleEquation(base,
		aimPoint).getDegreeFromCoodirate(aimPoint);

	currentAimingAngle_ = Default::fixAngle(currentAimingAngle_);

	currentAimingAngle_ = ((int)Default::round(
		currentAimingAngle_,
		aimingMeasure_));

	return currentAimingAngle_;
}

void AutoAimingObject::setBasicProperties()
{
	Object::setBasicProperties();
	target_ = nullptr;
	aimingMeasure_ = 1.0;
	currentAimingAngle_ = 0;
}

void AutoAimingObject::setAimingProperties(Object* target, double measure, T6Vec3 basePoint)
{
	target_ = target;
	aimingMeasure_ = measure;
	if (basePoint != POSITION_ZERO)
		this->basePoint_ = basePoint;
	else
		this->basePoint_ = position_;
}


