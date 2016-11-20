#include "StandCanon.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

DWORD StandCanon::lightColor_[] = { 0xFFFF8C7C, 0xFFE44434, 0xFFB81C0C, 0xFFE44434 };

int StandCanon::currentColor_ = 0;


StandCanon::StandCanon(T6Vec3 position, Object* target)
{
	setBasicProperties();
	this->position_ = position;

	setAimingProperties(target, STAND_CANON_DIT6RectION_MEASURE, position);

	Object::loadObjectResource(STAND_CANON_RESOURCE_LINK.c_str(), StandCanonStatus::NUM_OF_SC_STATUS, STAND_CANON_NUM_OF_MAP_COLOR, RESOURCE_MT);

	*this->objectDefRect_ = Default::createRectFromBottomCenter(position, (*sprites_)->getFrameSize());

}


StandCanon::~StandCanon()
{
}


unsigned int StandCanon::getScore()
{
	return SCORE_STAND_CANON;
}


void StandCanon::draw()
{
	if (mobState_ != MOBS_STATE_WAIT){
		if (status_ < APPEAR_COMPLETLY) {
			((T6_MergedTexture*)(*sprites_))->draw((shootDirection_)* 2 + 0, position_, 1.0f, 0.3f * status_, false, DrawCenter::BOTTOMCENTER);
			((T6_MergedTexture*)(*sprites_))->draw((shootDirection_)* 2 + 1, position_, 1.0f, 0.3f * status_, false, DrawCenter::BOTTOMCENTER, SCALE_NO, TRANSLATE_NO, ANGLE_NO, lightColor_[currentColor_]);
		}
		else{
			((T6_MergedTexture*)(*sprites_))->draw((shootDirection_)* 2 + 0, position_, DrawCenter::BOTTOMCENTER);
			((T6_MergedTexture*)(*sprites_))->draw((shootDirection_)* 2 + 1, position_, DrawCenter::BOTTOMCENTER, SCALE_NO, TRANSLATE_NO, ANGLE_NO, lightColor_[currentColor_]);
		}
	}

	this->lightTime_ += Timer::getRoundTime();

	if (lightTime_ >= STAND_CANON_LIGHT_TIME)
	{
		currentColor_ = (currentColor_ + 1) % STAND_CANON_NUM_OF_LIGHT_COLOR;
		lightTime_ = 0;
	}
}

void StandCanon::waitUpdate()
{
	if (Default::computeDistance(target_->getPosition(), position_) <= STAND_CANON_SHOOT_DISTANCE)
		activate();
}

void StandCanon::activateUpdate()
{
	ShootObject::update();
	checkIfShooted();

	if (status_ < StandCanonStatus::APPEAR_COMPLETLY)
	{
		if (timeCounter_ < STAND_CANON_ACTIVATE_TIME)
			timeCounter_ += Timer::getRoundTime();
		else
		{
			timeCounter_ = 0;
			status_++;
		}
	}
	else
	{
		rollUpdate();
		shootUpdate();
	}
}


void StandCanon::deadUpdate()
{
}

void StandCanon::setBasicProperties()
{
	ShootObject::setBasicProperties();
	Mobs::setBasicProperties();
	AutoAimingObject::setBasicProperties();

	Object::deactivate(PROPERTIES_VISIBLE);
	heathPoints_ = STAND_CANON_HEALTH_POINTS;
	this->status_ = StandCanonStatus::APPEAR_30_PERCENT;
	timeCounter_ = 0;
	shootDirection_ = 2;
}

void StandCanon::deadEffect()
{
	EffectManager::addExplode(position_);
}

void StandCanon::update()
{
	Mobs::update();
}

int StandCanon::computeShootAngle()
{
	return (shootDirection_ + 4) * STAND_CANON_DIT6RectION_MEASURE;
}

T6Vec3 StandCanon::computeShootPoint()
{
	return Default::computeCenter(*Object::objectDefRect_);
}


void StandCanon::rollUpdate()
{
	rotateDelay_ += Timer::getRoundTime();

	if (rotateDelay_ >= TIME_ROTATE_DELAY) {
		int requiredRollStepToAim = (int)(aim() / STAND_CANON_DIT6RectION_MEASURE + 0.5) - shootDirection_ - 4;

		if (STAND_CANON_CHECK_IF_SHOOT_ANGLE(Default::round(currentAimingAngle_, STAND_CANON_DIT6RectION_MEASURE)))
		{
			shootDirection_ += GET_SIGN(requiredRollStepToAim);
			rotateDelay_ = 0;
		}
	}
}


void StandCanon::shootUpdate()
{
	FOR(shootedBullets_.size())
		if (shootedBullets_.at(i) == nullptr) {
		shootedBullets_.erase(shootedBullets_.begin() + i);
		i--;
		}

	if (shootedBullets_.size() < STAND_CANON_MAX_BULLET_IN_A_ROW && timeCounter_ <= STAND_CANON_SHOOT_TIME)
		shootedBullets_.push_back(shoot());

	if (timeCounter_ > Timer::getRoundTime()) timeCounter_ -= Timer::getRoundTime();

	if (timeCounter_ <= Timer::getRoundTime())
	{
		timeCounter_ = STAND_CANON_RELOAD_TIME;
		shootedBullets_.clear();
	}
}

bool StandCanon::affect(Object* obj, DWORD key)
{
	return Mobs::affect(obj, key);
}

bool StandCanon::isTerminated()
{
	return Mobs::isTerminated();
}
