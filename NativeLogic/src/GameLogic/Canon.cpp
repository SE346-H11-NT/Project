#include "Canon.h"
#include "Map.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

DWORD Canon::lightColor_[] = { 0xFFFF8C7C, 0xFFE44434, 0xFFB81C0C };


Canon::Canon(T6Vec3 position, Object* target)
{
	setBasicProperties();
	setAimingProperties(target, CANON_DIT6RectION_MEASURE, position);
	Object::deactivate(PROPERTIES_VISIBLE);
	target_ = target;
	this->position_ = position;
	heathPoints_ = CANON_HEALTH_POINTS;

	Object::loadObjectResource(CANON_RESOURCE_LINK.c_str(), CanonStatus::NUM_OF_C_STATUS, CANON_NUM_OF_MAP_COLOR, RESOURCE_MT);

	*this->objectDefRect_ = Default::createRectFromCenter(position, CANON_BOUND_SIZE);
}


Canon::~Canon()
{
}



void Canon::activate()
{
	if (status_ < CanonStatus::OPENING) {
		status_ = CanonStatus::OPENING;
		timeCounter_ = (DWORD)CANON_ACTIVATE_TIME;
	}
	else if (timeCounter_ <= Timer::getRoundTime())
	{
		Mobs::activate();
		timeCounter_ = CANON_RELOAD_TIME;
	}
	else timeCounter_ -= Timer::getRoundTime();
}


unsigned int Canon::getScore()
{
	return SCORE_CANON;
}


int Canon::getShootDirection()
{
	return aim();
}


void Canon::update()
{
	Mobs::update();
}


void Canon::draw()
{
	if (status_ >= CanonStatus::CLOSE && mobState_ == MOBS_STATE_WAIT)
	{
		((T6_MergedTexture*)(*sprites_))->draw(status_ * 2 + 0, position_, DrawCenter::CENTER);
		((T6_MergedTexture*)(*sprites_))->draw(status_ * 2 + 1, position_, DrawCenter::CENTER, SCALE_NO, TRANSLATE_NO, ANGLE_NO, lightColor_[currentColor_]);
	}
	else
	{
		((T6_MergedTexture*)(*sprites_))->draw(shootDirection_ * 2 + 0, position_, DrawCenter::CENTER);
		((T6_MergedTexture*)(*sprites_))->draw(shootDirection_ * 2 + 1, position_, DrawCenter::CENTER, SCALE_NO, TRANSLATE_NO, ANGLE_NO, lightColor_[currentColor_]);
	}
	this->lightTime_ += Timer::getRoundTime();
	if (lightTime_ >= CANON_LIGHT_TIME)
	{
		currentColor_ = (currentColor_ + 1) % CANON_NUM_OF_LIGHT_COLOR;
		lightTime_ = 0;
	}
}


void Canon::setBasicProperties()
{
	ShootObject::setBasicProperties();
	AutoAimingObject::setBasicProperties();
	Mobs::setBasicProperties();

	deactivate(PROPERTIES_VISIBLE);
	this->currentBullet_ = MOBS;
	this->status_ = CanonStatus::CLOSE;
	this->rotateDelay_ = TIME_ROTATE_DELAY;
	this->shootDirection_ = 0;
}

void Canon::waitUpdate()
{
	if (Default::computeDistance(target_->getPosition(), position_) <= CANON_SHOOT_DISTANCE)
		activate();
}

void Canon::activateUpdate()
{
	ShootObject::update();
	checkIfShooted();

	if (!rollUpdate())
		shootUpdate();
}

void Canon::deadUpdate()
{
}

void Canon::deadEffect()
{
	EffectManager::addExplode(position_);
}

int Canon::computeShootAngle()
{
	return currentAimingAngle_;
}

T6Vec3 Canon::computeShootPoint()
{
	return position_;
}


bool Canon::rollUpdate()
{
	rotateDelay_ += Timer::getRoundTime();
	int rollStep = (int)(aim() / CANON_DIT6RectION_MEASURE + 0.5) - shootDirection_;

	if (rotateDelay_ >= TIME_ROTATE_DELAY) {

		if (CANON_NUM_OF_DIT6RectION - abs(rollStep) < abs(rollStep))
		{
			shootDirection_ -= GET_SIGN(rollStep);
			if (shootDirection_ < 0)
				shootDirection_ += CANON_NUM_OF_DIT6RectION;
		}
		else
		{
			shootDirection_ += GET_SIGN(rollStep);
		}

		shootDirection_ = shootDirection_ % CANON_NUM_OF_DIT6RectION;

		rotateDelay_ = 0;
	}

	if (rollStep != 0)
		return true;
	return false;
}


void Canon::shootUpdate()
{
	FOR(shootedBullets_.size())
		if (shootedBullets_.at(i) == nullptr) {
		shootedBullets_.erase(shootedBullets_.begin() + i);
		i--;
		}

	if (shootedBullets_.empty() && timeCounter_ <= CANON_SHOOT_TIME)
		shootedBullets_.push_back(shoot());

	if (timeCounter_ > Timer::getRoundTime()) timeCounter_ -= Timer::getRoundTime();

	if (timeCounter_ <= Timer::getRoundTime())
	{
		timeCounter_ = CANON_RELOAD_TIME;
		shootedBullets_.clear();
	}
}

bool Canon::affect(Object* obj, DWORD key)
{
	return false;
}

bool Canon::isTerminated()
{
	switch (Map::getCameraType())
	{
	case CAMERA_X:
		return (isDead() | (objectDefRect_->right < Camera::getViewPort().left));
		break;
	case CAMERA_Y:
		return (isDead() | (objectDefRect_->top < Camera::getViewPort().bottom));
		break;
	default:
		break;
	}

	return false;
}
