#include "BulletSpread.h"
#include "BulletManager.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif


BulletSpread::BulletSpread()
{
	Bullet::setBasicProperties();
	bulletRS_ = BulletRS::MACHINE;
	damage_ = BULLET_DAMAGE_M;
}


BulletSpread::~BulletSpread()
{
}


BulletType BulletSpread::getType()
{
	return BulletType::S;
}


void BulletSpread::shoot(int angle, T6Vec3 startPoint, int ally, float scaleX)
{
	static BULLET_S_SPREAD_ANGLE;
	int* counter = &manager_->getCounter(getType());
	instances_.clear();

	FOR(BULLET_S_SPREAD_LEVEL)
		if (*counter >= 0)
		{
			SOUND_CODE(FreeSound::play(BULLET_S_SOUND));
			T6Vec3 velo = T6Vec3(BULLET_S_MOVE_SPEED * Default::cos(DEGREE_TO_RADIAN(angle + spreadAngle[i])),
							   			   BULLET_S_MOVE_SPEED * Default::sin(DEGREE_TO_RADIAN(angle + spreadAngle[i])),
										   0.0F);

			Bullet* shootedOne = manager_->getPool(getType())[*counter];

			shootedOne->setProperties(angle + spreadAngle[i], ally, scaleX);
			shootedOne->shoot(velo, startPoint, ally, scaleX);
			instances_.push_back(shootedOne);
		}
	else break;
}


void BulletSpread::shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX)
{
	flydistance_ = 0;

	position_ = startPoint;

	this->setVelo(velocity);

	*objectDefRect_ = Default::createRectFromCenter(position_, BULLET_SIZE_S);

	managerProcessing();
}



void BulletSpread::update()
{
	MoveObject::update(Timer::getRoundTime(), Default::createRectFromCenter, BULLET_SIZE_S, UPDATE_XY);
	flydistance_ += TRUE_SPEED(BULLET_S_MOVE_SPEED, Timer::getRoundTime());
	generateBullet();
}



T6Vec3 BulletSpread::generateBullet()
{
	return Object::position_;
}

void BulletSpread::draw()
{
	if (rendered_)
		(*sprites_)->render(Timer::getRoundTime(), position_, ANGLE_NO, SCALE_A(((float)flydistance_ / RESOLUTION_WIDTH) / 3.0F + 0.75F),
		TRANSLATE_NO, DrawCenter::CENTER, COLOR_NO, bulletRS_, bulletRS_);
}

void BulletSpread::increaseVelocity(int bonusSpeed)
{
	FOR(instances_.size())
		instances_.at(i)->setVelo(*instances_.at(i)->getVelo() + 
		T6Vec3(bonusSpeed * Default::cos(DEGREE_TO_RADIAN(instances_.at(i)->getShootAngle())),
					bonusSpeed * Default::sin(DEGREE_TO_RADIAN(instances_.at(i)->getShootAngle())),
		0.0f));
}
