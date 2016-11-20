#include "TankGun.h"


TankGun::TankGun(T6Vec3 pos, Object* theHost, Object* target)
{
	position_ = pos;
	theHost_ = theHost;
	distance_ = position_ - theHost->getPosition();
	target_ = target;
	setBasicProperties();
	Object::loadObjectResource(GUN_RESOURCE_LINK.c_str(), GUN_RESOURCE_ROWS, GUN_RESOURCE_COLUMNS, RESOURCE_MT);
}


TankGun::~TankGun()
{
}

unsigned int TankGun::getScore()
{
	return 0;
}

void TankGun::draw()
{
	((T6_MergedTexture*)*sprites_)->draw(status_ * 2 + 0, getPosition(), DrawCenter::TOPLEFT, scale_);
	((T6_MergedTexture*)*sprites_)->draw(status_ * 2 + 1, getPosition(), DrawCenter::TOPLEFT, scale_, TRANSLATE_NO, ANGLE_NO, fadeColor_);
}

void TankGun::waitUpdate()
{
}

void TankGun::activateUpdate()
{
	rotateTimeCounter_ += Timer::getRoundTime();
	shootDelay_ += Timer::getRoundTime();

	int status = GUN_STATUS_BY_AIM_ANGLE_AND_SCALEX(AutoAimingObject::aim(), scale_.x);

	if (rotateTimeCounter_ >= GUN_ROTATE_DELAY)
	{
		if (status > status_ && status_ < (GUN_RESOURCE_ROWS - 1))
		{
			status_++;
			rotateTimeCounter_ = 0;
		}
		else if (status < status_ && status_ > 0)
		{
			status_--;
			rotateTimeCounter_ = 0;
		}
	}

	if (shootDelay_ >= GUN_SHOOT_DELAY)
	{
		if (shoot() != nullptr)
		{
			bulletCounter_++;
			if (bulletCounter_ >= GUN_BULLET_ROW)
			{
				bulletCounter_ = 0;
				shootDelay_ = 0;
			}
		}
	}
}

void TankGun::deadUpdate()
{
	// Do nothing
}

bool TankGun::affect(Object* obj, DWORD key)
{
	return false;
}

void TankGun::setBasicProperties()
{
	Mobs::setBasicProperties();
	ShootObject::setBasicProperties();
	AutoAimingObject::setBasicProperties();
	MoveObject::setBasicProperties();
	AutoAimingObject::setAimingProperties(target_, GUN_AIMING_MEASURE, getPosition());

	scale_ = theHost_->getScale();
	currentBullet_ = BulletType::MOBS;
	rotateTimeCounter_ = 0;
	shootDelay_ = GUN_SHOOT_DELAY;
	Object::activate(PROPERTIES_EVATION);
	fadeColor_ = 0xFFFF0000;
}

void TankGun::deadEffect()
{
	// Do nothing
}

void TankGun::update()
{
	Mobs::update();
	ShootObject::update();
	position_ = theHost_->getPosition() + distance_;
}

bool TankGun::isTerminated()
{
	return false;
}

int TankGun::computeShootAngle()
{
	return ((status_ * GUN_AIMING_MEASURE) * (scale_.x > 0 ? -1 : 1) + (90.0F - GET_SIGN(scale_.x) * 90.0F));
}

T6Vec3 TankGun::computeShootPoint()
{
	static GUN_SHOOTPOINTS_FIX;

	T6Vec3 result = getPosition();
	result.x += shootPointFixes[status_].x * scale_.x;
	result.y += shootPointFixes[status_].y * scale_.y;

	return result;
}

void TankGun::setColor(DWORD color)
{
	fadeColor_ = color;
}
