#include "CrystalOrb.h"


CrystalOrb::CrystalOrb(T6Vec3 position, Object* target)
{
	setBasicProperties();

	setPos(position);

	AutoAimingObject::setAimingProperties(target, CRYSTAL_AIMING_MEASURE);

	Object::loadObjectResource(CRYSTAL_RESOURCE_LINK.c_str(), CRYSTAL_RESOURCE_ROWS, CRYSTAL_RESOURCE_COLUMNS, RESOURCE_MS);
}


CrystalOrb::~CrystalOrb()
{
}

void CrystalOrb::setBasicProperties()
{
	MetalOrb::setBasicProperties();
	ShootObject::setBasicProperties();
	AutoAimingObject::setBasicProperties();
	currentBullet_ = BulletType::FIRE_CIRCLE;
	timeCounter_ = 0;
	heathPoints_ = CRYSTAL_LIFE_POINTS;
}

int CrystalOrb::computeShootAngle()
{
	return aim();
}

T6Vec3 CrystalOrb::computeShootPoint()
{
	return position_;
}

void CrystalOrb::update()
{
	Mobs::update();
}

void CrystalOrb::draw()
{
	MetalOrb::draw();
}

bool CrystalOrb::affect(Object* obj, DWORD key)
{
	return Mobs::affect(obj, key);
}

bool CrystalOrb::isTerminated()
{
	return isDead();
}

void CrystalOrb::activateUpdate()
{
	ShootObject::update();
	BulletManager::updateIfObjectIsShooted(this, KEY_NO);

	timeCounter_ += Timer::getRoundTime();
	if (timeCounter_ >= CRYSTAL_SHOOT_DELAY)
	{
		instanceShoot();
		timeCounter_ = 0;
	}
}