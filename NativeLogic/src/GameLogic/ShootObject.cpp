#include "ShootObject.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif


Bullet* ShootObject::shoot(T6Vec3 velocity)
{
	static RELOAD_TIME;
	if (lastShootTime_ >= reload[currentBullet_]) {

		lastShootTime_ = Timer::getRoundTime();

		if (velocity == SPEED_NO)
		{
			return BulletManager::getInstance().shoot(currentBullet_, ALLY_MOBS, computeShootPoint(), computeShootAngle(), scale_.x);
		}
		else
		{
			return BulletManager::getInstance().shoot(currentBullet_, ALLY_MOBS, computeShootPoint(), velocity, scale_.x);
		}
	}

	return nullptr;
}


void ShootObject::changeBullet(BulletType newBullet)
{
	currentBullet_ = newBullet;
}



void ShootObject::update()
{
	static RELOAD_TIME;
	if (lastShootTime_ < reload[currentBullet_]) {
		lastShootTime_ += Timer::getRoundTime();
	}
}



void ShootObject::setBasicProperties()
{
	Object::setBasicProperties();
	currentBullet_ = BulletType::BASIC;
	lastShootTime_ = 0;
}


int ShootObject::getShootDirection(T6Vec3* target)
{
	return (int)RADIAN_TO_DEGREE(T6_Math::caculateLineAngle(position_, *target));
}

bool ShootObject::affect(Object* obj, DWORD key)
{
	return false;
}

Bullet* ShootObject::instanceShoot(T6Vec3 velocity /*= SPEED_NO*/)
{
	static RELOAD_TIME;
	lastShootTime_ = reload[(currentBullet_)];
	return shoot(velocity);
}
