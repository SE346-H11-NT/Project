#include "BulletLaser.h"
#include "BulletManager.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

int BulletLaser::laserCounter = 0;

BulletLaser::BulletLaser()
{
	Bullet::setBasicProperties();
	bulletRS_ = BulletRS::LAZER;
	damage_ = BULLET_DAMAGE_L;
}


BulletLaser::~BulletLaser()
{
}


BulletType BulletLaser::getType()
{
	return BulletType::L;
}


void BulletLaser::shoot(int angle, T6Vec3 startPoint, int ally, float scaleX)
{
	laserCounter = 0;

	setProperties(angle, ally, scaleX);

	SOUND_CODE(FreeSound::play(BULLET_L_SOUND));

	(manager_->getPool(getType())[manager_->getCounter(getType())])->shoot(
		T6Vec3(BULLET_L_MOVE_SPEED * Default::cos(DEGREE_TO_RADIAN(angle)),
					BULLET_L_MOVE_SPEED * Default::sin(DEGREE_TO_RADIAN(angle)),
					0.0F), 
					startPoint, 
					ally, 
					scaleX);
}


void BulletLaser::shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX)
{
	this->setVelo(velocity);
	startPoint.x += BULLET_L_LATE_START * Default::cos(DEGREE_TO_RADIAN(shootAngle_));
	startPoint.y += BULLET_L_LATE_START * Default::sin(DEGREE_TO_RADIAN(shootAngle_));

	position_ = startPoint;
	isGenerated_ = false;
	movedDistance_ = 0.0F;

	generateBullet();

	managerProcessing();
}



void BulletLaser::update()
{
	MoveObject::update(Timer::getRoundTime(), Default::createRectFromCenter, BULLET_SIZE_L, UPDATE_XY);

	movedDistance_ += TRUE_SPEED(BULLET_L_MOVE_SPEED, Timer::getRoundTime());

	if (movedDistance_ >= abs(BULLET_L_LATE_START) && !isGenerated_)
	{
		isGenerated_ = true;
		if (manager_->getCounter(getType()) >= 0 && laserCounter < (BULLET_MAX_L - 1))
		{
			laserCounter++;
			T6Vec3 startPoint = getPosition();

			if (!isTerminated())
				startPoint.x += BULLET_L_LATE_START * Default::cos(DEGREE_TO_RADIAN(shootAngle_));
			startPoint.y += BULLET_L_LATE_START * Default::sin(DEGREE_TO_RADIAN(shootAngle_));

			Bullet* shootedOne = manager_->getPool(getType())[manager_->getCounter(getType())];
			shootedOne->setProperties(shootAngle_, ally_, scaleX_);
			shootedOne->shoot(*getVelo(), startPoint, ally_, scaleX_);
		}
		else
			laserCounter = 0;
	}
}



T6Vec3 BulletLaser::generateBullet()
{
	return Object::position_;
}

void BulletLaser::draw()
{
	if (rendered_)
		(*sprites_)->render(Timer::getRoundTime(), position_,
		(float)shootAngle_ + (shootAngle_ % 90 != 0 ?
		ANGLE_COUNTER_CLOCKWISE(90) + 2 * (ANGLE_COUNTER_CLOCKWISE(45) - shootAngle_ % 90) :
		0),
		SCALE_XY(scaleX_, 1.0F),
		TRANSLATE_NO, DrawCenter::CENTER, COLOR_NO, bulletRS_, bulletRS_);

#if GAMEMODE == GAMEMODE_FLASH_BULLET
	rendered_ = !rendered_;
#endif
}