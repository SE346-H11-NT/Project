#include "BulletBasic.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif


BulletBasic::BulletBasic(int ally)
{
	Bullet::setBasicProperties();
	bulletRS_ = BulletRS::AMMO;
	damage_ = BULLET_DAMAGE_BASIC;

	if (ally == ALLY_PLAYER)
		type_ = BulletType::BASIC;
	else
		type_ = BulletType::MOBS;
}


BulletBasic::~BulletBasic()
{
}


BulletType BulletBasic::getType()
{
	return type_;
}


void BulletBasic::shoot(int angle, T6Vec3 startPoint, int ally, float scaleX)
{
	setProperties(angle, ally, scaleX);

	T6Vec3 velo = T6Vec3(BULLET_BASIC_MOVE_SPEED * Default::cos(DEGREE_TO_RADIAN(angle)),
								  BULLET_BASIC_MOVE_SPEED * Default::sin(DEGREE_TO_RADIAN(angle)),
								  0.0F);

	if (ally_ == ALLY_MOBS)
	{
		velo /= 2;
	}

	shoot(velo, startPoint, ally, scaleX);
}


void BulletBasic::shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX)
{
	position_ = startPoint;

	setVelo(velocity);

	*objectDefRect_ = Default::createRectFromCenter(position_, BULLET_SIZE_BASIC);
	managerProcessing();
}



void BulletBasic::update()
{
	MoveObject::update(Timer::getRoundTime(), Default::createRectFromCenter, BULLET_SIZE_BASIC, UPDATE_XY);

	generateBullet();
}



T6Vec3 BulletBasic::generateBullet()
{
	return Object::position_;
}