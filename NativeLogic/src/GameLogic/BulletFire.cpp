#include "BulletFire.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif


BulletFire::BulletFire()
{
	Bullet::setBasicProperties();
	bulletRS_ = BulletRS::FIRE;
	damage_ = BULLET_DAMAGE_F;
}


BulletFire::~BulletFire()
{
}


BulletType BulletFire::getType()
{
	return BulletType::F;
}


void BulletFire::shoot(int angle, T6Vec3 startPoint, int ally, float scaleX)
{
	setProperties(angle, ally, scaleX);

	this->selfRotateDegree_ = angle + ANGLE_COUNTER_CLOCKWISE(180);

	shoot(T6Vec3(BULLET_F_MOVE_SPEED * Default::cos(DEGREE_TO_RADIAN(angle)),
						BULLET_F_MOVE_SPEED * Default::sin(DEGREE_TO_RADIAN(angle)),
						0.0F),
			startPoint,
			ally,
			scaleX);
}


void BulletFire::shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX)
{
	startPoint = CircleEquation(startPoint.x, startPoint.y, BULLET_F_ROUND_RANGE).getCoodirateFromDegree(shootAngle_);
	setVelo(velocity);

	centerPos_ = startPoint;
	position_ = POSITION_ZERO;

	generateBullet();
	managerProcessing();
}



void BulletFire::update()
{
	Default::swap(centerPos_, position_);
	MoveObject::update(Timer::getRoundTime(), Default::createRectFromCenter, BULLET_SIZE_F, UPDATE_XY);
	Default::swap(centerPos_, position_);

	generateBullet();
}



T6Vec3 BulletFire::generateBullet()
{
	position_ = CircleEquation(centerPos_.x, centerPos_.y, BULLET_F_ROUND_RANGE).getCoodirateFromDegree(selfRotateDegree_);

	selfRotateDegree_ += (int)(scaleX_ * TRUE_SPEED(BULLET_F_ROUND_SPEED, (float)Timer::getRoundTime()));
	selfRotateDegree_ = selfRotateDegree_ % ANGLE_DEGREE_LIM;

	*Object::objectDefRect_ = Default::createRectFromCenter(position_, BULLET_SIZE_F);

	return position_;
}

void BulletFire::draw()
{
	if (rendered_)
		(*sprites_)->render(Timer::getRoundTime(), position_, ANGLE_NO, SCALE_NO,
		TRANSLATE_NO, DrawCenter::CENTER, COLOR_NO, bulletRS_, bulletRS_);

#if GAMEMODE == GAMEMODE_FLASH_BULLET
	rendered_ = !rendered_;
#endif
}
