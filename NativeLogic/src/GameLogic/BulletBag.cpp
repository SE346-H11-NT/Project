#include "BulletBag.h"
#include "Map.h"


BulletBag::BulletBag()
{
}


BulletBag::BulletBag(T6Vec3 position, BulletFalconType containFalconType)
{
	setBasicProperties();
	position_ = position;
	containFalconType_ = containFalconType;
	*objectDefRect_ = Default::createRectFromCenter(position, BULLET_BAG_SIZE);
	Object::loadObjectResource(BULLET_BAG_LINK.c_str(), BULLET_BAG_RESOURCE_ROWS, BULLET_BAG_RESOURCE_COLUMNS, RESOURCE_MT);
}


BulletBag::~BulletBag()
{
}

void BulletBag::update()
{
	DestroyableObject::update();
	checkIfShooted();

	if (isDead())
	{
		Map::generateFalcon(getPosition(), containFalconType_);
		isTerminated_ = true;
	}

	switch (status_)
	{
	case BulletBagStatus::BULLET_BAG_CLOSE:
		if (checkIfTimeCounted(BULLET_BAG_CLOSE_TIME))
		{
			status_ = BulletBagStatus::BULLET_BAG_OPENING;
			isOpening_ = true;
		}
		break;

	case BulletBagStatus::BULLET_BAG_OPENING:
		if (checkIfTimeCounted(BULLET_BAG_OPENING_TIME))
		{
			if (isOpening_)
			{
				status_ = BulletBagStatus::BULLET_BAG_OPEN;
				deactivate(PROPERTIES_IMMORTAL);
			}
			else
			{
				status_ = BulletBagStatus::BULLET_BAG_CLOSE;
				activate(PROPERTIES_IMMORTAL);
			}
		}
		break;

	case BulletBagStatus::BULLET_BAG_OPEN:
		if (checkIfTimeCounted(BULLET_BAG_OPEN_TIME))
		{
			status_ = BulletBagStatus::BULLET_BAG_OPENING;
			isOpening_ = false;
		}
		break;

	default:
		break;
	}
}

void BulletBag::setBasicProperties()
{
	DestroyableObject::setBasicProperties();
	deactivate(PROPERTIES_VISIBLE);
	activate(PROPERTIES_IMMORTAL);
	status_ = BulletBagStatus::BULLET_BAG_CLOSE;
	containFalconType_ = BulletFalconType::FALCON_S;
	bagColor_ = 0;
	lightTime_ = 0;
	isOpening_ = true;
	isTerminated_ = false;
	counter_ = 0;
}

void BulletBag::draw()
{
	static BLENDED_COLOR_LIST;
	lightTime_ += Timer::getRoundTime();
	if (lightTime_ >= BULLET_BAG_SWITCH_COLOR_TIME)
	{
		lightTime_ = 0;
		bagColor_ = (bagColor_ + 1) % NUM_OF_BLENDED_COLORS;
	}

	((T6_MergedTexture*)*sprites_)->draw(status_ * 2 + 0, position_, DrawCenter::CENTER);
	((T6_MergedTexture*)*sprites_)->draw(status_ * 2 + 1, position_, DrawCenter::CENTER, SCALE_NO, TRANSLATE_NO, ANGLE_NO, color[bagColor_]);
}

void BulletBag::deadEffect()
{
	EffectManager::addExplode(position_);
}

bool BulletBag::affect(Object* obj, DWORD key)
{
	return false;
}


bool BulletBag::checkIfTimeCounted(DWORD time)
{
	counter_ += Timer::getRoundTime();
	if (counter_ >= time)
	{
		counter_ = 0;
		return true;
	}

	return false;
}


bool BulletBag::isTerminated()
{
	if (!isTerminated_)
	{
		return DestroyableObject::isTerminated();
	}

	return true;
}
