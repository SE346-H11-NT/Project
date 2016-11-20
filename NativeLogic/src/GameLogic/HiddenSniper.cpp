#include "HiddenSniper.h"


HiddenSniper::HiddenSniper(T6Vec3 position, Object* target, Size visiblePercent, int numOfShootDirection)
{
	setBasicProperties();
	position_ = position;
	visiblePercent_ = visiblePercent;
	numOfShootDirection_ = numOfShootDirection;

	*objectDefRect_ = Default::createRectFromBottomCenter(position, HIDDEN_SNIPER_BOUND_SIZE);
	setAimingProperties(target, HIDDEN_SNIPER_DIT6RectION_MEASURE(numOfShootDirection_), Default::computeCenter(*objectDefRect_));

	currentBullet_ = BulletType::MOBS;
	Object::loadObjectResource(HiddenSniperStatus::NUM_OF_HIDDEN_SNIPER_STATUS, LINK_HIDDEN_SNIPER);
	((T6_Sprite*)sprites_[HiddenSniperStatus::HIDDEN_SNIPER_HIDE])->setFrameTime(DEFAULT_FRAME_TIME * 2);
}


HiddenSniper::~HiddenSniper()
{
}

void HiddenSniper::setBasicProperties()
{
	Mobs::setBasicProperties();
	AutoAimingObject::setBasicProperties();
	ShootObject::setBasicProperties();

	status_ = HiddenSniperStatus::HIDDEN_SNIPER_HIDE;
}

void HiddenSniper::update()
{
	Mobs::update();
}

void HiddenSniper::draw()
{
	if (isDead())
	{
		return;
	}

	int sx = GET_SIGN((int)(target_->getPosition().x - getPosition().x));
	sx != 0 ? scale_.x = (float)sx : 0;

	if (mobState_ == MOBS_STATE_WAIT)
		if (shootedBullet_ == nullptr)
			sprites_[status_]->render(0, position_, ANGLE_NO, scale_, TRANSLATE_NO, DrawCenter::BOTTOMLEFT);
		else
		{
			sprites_[status_]->render(Timer::getRoundTime(), position_,
				ANGLE_NO, scale_, TRANSLATE_NO, DrawCenter::BOTTOMLEFT,
				COLOR_NO, -1, 0);

			if (((T6_Sprite*)sprites_[status_])->isComplete())
				shootedBullet_ = nullptr;
		}
	else if (mobState_ == MOBS_STATE_ACTIVATE)
	{
		if (status_ == HiddenSniperStatus::HIDDEN_SNIPER_HIDE)
		{
			if (shootedBullet_ == nullptr)
			{
				sprites_[status_]->render(Timer::getRoundTime(), position_, ANGLE_NO,
					scale_, TRANSLATE_NO, DrawCenter::BOTTOMLEFT);

				if (((T6_Sprite*)sprites_[status_])->isComplete())
					status_ = (int)((currentAimingAngle_ % 180 == 0 ? 0 : (1 + currentAimingAngle_ / 180)));
			}
		}
		else
		{
			sprites_[status_]->render(
				Timer::getRoundTime(), position_, visiblePercent_.width, visiblePercent_.height, false, scale_, DrawCenter::BOTTOMLEFT);
		}
	}
}

unsigned int HiddenSniper::getScore()
{
	return SCORE_SNIPER;
}

void HiddenSniper::waitUpdate()
{
	if (Default::computeDistance(target_->getPosition(), position_) <= HIDDEN_SNIPER_SHOOT_DISTANCE)
		if (checkCounter(HIDDEN_SNIPER_RELOAD_TIME))
			activate();
}

void HiddenSniper::activateUpdate()
{
	ShootObject::update();
	checkIfShooted();

	if (status_ != HIDDEN_SNIPER_HIDE)
	{
		if (shootedBullet_ == nullptr)
		{
			shootedBullet_ = shoot();
		}
		else if (checkCounter(HIDDEN_SNIPER_SHOOT_TIME))
		{
			status_ = HiddenSniperStatus::HIDDEN_SNIPER_HIDE;
			suspend();
		}
	}
}

void HiddenSniper::deadUpdate()
{
}

void HiddenSniper::deadEffect()
{
	T6Vec3 effectPos(position_);
	effectPos.y += (float)(sprites_[status_]->getFrameSize().height / 2.0f);

	EffectManager::addSmallExplode(effectPos);
}

bool HiddenSniper::checkCounter(DWORD countTime)
{
	static DWORD counter = 0;

	counter += Timer::getRoundTime();

	if (counter >= countTime)
	{
		counter = 0;
		return true;
	}
	return false;
}

int HiddenSniper::computeShootAngle()
{
	return (aim());
}

T6Vec3 HiddenSniper::computeShootPoint()
{
	T6Vec3 result = position_;

	result.x += scale_.x * sprites_[status_]->getFrameSize().width / 2;
	result.x += (1 - visiblePercent_.width) * sprites_[status_]->getFrameSize().width;
	result.y -= (1 - visiblePercent_.height) * sprites_[status_]->getFrameSize().height;

	switch (status_)
	{
	case HIDDEN_SNIPER_STRAIGHT:
		result.y += HS_HEIGHT_FOOT_TO_STRAIGHT_GUN;
		break;

	case HIDDEN_SNIPER_UP45:
		result.y += sprites_[status_]->getFrameSize().height;
		break;

	case HIDDEN_SNIPER_DOWN45:
		result.y += HS_HEIGHT_FOOT_TO_DOWN45_GUN;
		break;

	default:
		break;
	}

	return result;
}


bool HiddenSniper::affect(Object* obj, DWORD key)
{
	return Mobs::affect(obj, key);
}

bool HiddenSniper::isTerminated()
{
	return Mobs::isTerminated();
}

void HiddenSniper::updateAsBossSubpart()
{
	update();
}
