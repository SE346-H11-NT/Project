#include "BulletMachine.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif


BulletMachine::BulletMachine()
{
	Bullet::setBasicProperties();
	bulletRS_ = BulletRS::MACHINE;
	damage_ = BULLET_DAMAGE_M;
}

BulletMachine::BulletMachine(int ally)
{
	Bullet::setBasicProperties();
	bulletRS_ = BulletRS::MACHINE;
	damage_ = BULLET_DAMAGE_M;
	this->ally_ = ally;
}


BulletMachine::~BulletMachine()
{
}


BulletType BulletMachine::getType()
{
	return BulletType::M;
}


void BulletMachine::shoot(int angle, T6Vec3 startPoint, int ally, float scaleX)
{
	setProperties(angle, ally, scaleX);

	shoot(T6Vec3(BULLET_M_MOVE_SPEED * Default::cos(DEGREE_TO_RADIAN(angle)),
					  BULLET_M_MOVE_SPEED * Default::sin(DEGREE_TO_RADIAN(angle)),
					  0.0F),
					  startPoint,
					  ally,
					  scaleX);
}


void BulletMachine::shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX)
{
	setVelo(velocity);

	position_ = startPoint;

	*objectDefRect_ = Default::createRectFromCenter(position_, BULLET_SIZE_M);

	SOUND_CODE(FreeSound::play(BULLET_M_SOUND));

	managerProcessing();
}



void BulletMachine::update()
{
	MoveObject::update(Timer::getRoundTime(), Default::createRectFromCenter, BULLET_SIZE_M, UPDATE_XY);

	generateBullet();
}



T6Vec3 BulletMachine::generateBullet()
{
	return Object::position_;
}