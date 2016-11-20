#include "FloatingBulletBag.h"


FloatingBulletBag::FloatingBulletBag(T6Vec3 position, BulletFalconType containFalconType, T6Vec3 velocity)
{
	setBasicProperties();
	position_ = position;
	setVelo(velocity);
	if (getVelo()->x == 0)
		flyStraightAxis_ = AXIS_Y;
	else
		flyStraightAxis_ = AXIS_X;
	containFalconType_ = containFalconType;
	*objectDefRect_ = Default::createRectFromCenter(position, FLOATING_BULLET_BAG_SIZE);
	Object::loadObjectResource(
				FLOATING_BULLET_BAG_LINK.c_str(),
				FLOATING_BULLET_BAG_RESOURCE_ROWS,
				FLOATING_BULLET_BAG_RESOURCE_COLUMNS,
				RESOURCE_MS);
}


FloatingBulletBag::~FloatingBulletBag()
{
}

void FloatingBulletBag::update()
{
	switch (bagState_)
	{
	case FBS_WAIT:
		if (!Default::checkIfBounded(objectDefRect_, &Camera::getViewPort()))
		{
			if (flyStraightAxis_ == AXIS_X)
			{
				if (objectDefRect_->right < Camera::getViewPort().left)
					bagState_ = FloatingBulletBagStatus::FBS_FLY;
			}
			else
				if (objectDefRect_->top < Camera::getViewPort().bottom)
					bagState_ = FloatingBulletBagStatus::FBS_FLY;
		}
		break;
	case FBS_FLY:
		MoveObject::update(Timer::getRoundTime(), Default::createRectFromCenter, FLOATING_BULLET_BAG_SIZE, UPDATE_XY);

		currentDirectAngle_ += (int)TRUE_SPEED(FLOATING_BULLET_REDIT6RectING_SPEED, Timer::getRoundTime()) % ANGLE_DEGREE_LIM;

		setVelo(computeVelocity());

		BulletManager::updateIfObjectIsShooted(this, KEY_DESTROYABLE | KEY_MOVEABLE);
		if (isDead())
		{
			Map::generateFalcon(getPosition(), containFalconType_);
			isTerminated_ = true;
		}
		break;
	default:
		break;
	}
}

void FloatingBulletBag::setBasicProperties()
{
	DestroyableObject::setBasicProperties();
	MoveObject::setBasicProperties();
	gravity_ = &gravityNO;
	containFalconType_ = BulletFalconType::FALCON_S;
	isTerminated_ = false;
	bagState_ = FloatingBulletBagStatus::FBS_WAIT;
	currentDirectAngle_ = 0;
}

void FloatingBulletBag::draw()
{
	if (bagState_ == FloatingBulletBagStatus::FBS_FLY)
	(*sprites_)->drawImage(position_);
}

void FloatingBulletBag::deadEffect()
{
	EffectManager::addExplode(position_);
}

bool FloatingBulletBag::affect(Object* obj, DWORD key)
{
	return false;
}

bool FloatingBulletBag::isTerminated()
{
	return isTerminated_;
}


T6Vec3 FloatingBulletBag::computeVelocity()
{
	T6Vec3 result;

	if (flyStraightAxis_ == AXIS_X)
	{
		result.x = getVelo()->x;
		result.y = FLOATING_BULLET_REDIT6RectING_CAP * Default::sin(DEGREE_TO_RADIAN(currentDirectAngle_));
	}
	else
	{
		result.x = FLOATING_BULLET_REDIT6RectING_CAP * Default::cos(DEGREE_TO_RADIAN(currentDirectAngle_));
		result.y = getVelo()->y;
	}
		result.z = 0.0F;

	return result;
}
