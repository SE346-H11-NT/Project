#include "BlueBoom.h"


BlueBoom::BlueBoom(T6Vec3 pos)
{
	setBasicProperties();
	position_ = pos;
	*objectDefRect_ = Default::createRectFromCenter(getPosition(), BLUE_BOOM_THROW_SIZE);
	Object::loadObjectResource(BLUE_BOOM_RESOURCE_LINK.c_str(), BLUE_BOOM_RESOURCE_ROWS, BLUE_BOOM_RESOURCE_COLUMNS, RESOURCE_MS);
}


BlueBoom::~BlueBoom()
{
}

void BlueBoom::update()
{
	Mobs::update();
}

void BlueBoom::draw()
{
	if (!isTouchable())
	{
		(*sprites_)->drawImage(getPosition(), nullptr, SCALE_NO, TRANSLATE_NO, DrawCenter::CENTER, currentAngle_);
	}
}

bool BlueBoom::isTerminated()
{
	return (timeCounter_ >= BLUE_BOOM_EXPLODE_TIME);
}

bool BlueBoom::affect(Object* obj, DWORD key)
{
	return Mobs::affect(obj, key);
}

void BlueBoom::setBasicProperties()
{
	MoveObject::setBasicProperties();
	Mobs::setBasicProperties();

	timeCounter_ = 0;
	Object::deactivate(PROPERTIES_VISIBLE);
	MoveObject::setVelo(BLUE_BOOM_START_VELO);
}

unsigned int BlueBoom::getScore()
{
	return 0;
}

void BlueBoom::waitUpdate()
{
	MoveObject::updateMoveableWithCollision(BLUE_BOOM_THROW_SIZE, false, 0, Default::createRectFromCenter);
	currentAngle_ = Default::fixAngle(currentAngle_ + TRUE_SPEED(BLUE_BOOM_ROOL_SPEED, Timer::getRoundTime()));

	if (currentCollisEvents_.size() > 0)
	{
		activate();
	}
}

void BlueBoom::activateUpdate()
{
	timeCounter_ += Timer::getRoundTime();
}

void BlueBoom::deadUpdate()
{
	// Do nothing
}

void BlueBoom::activate()
{
	Mobs::activate();

	Object::activate(PROPERTIES_VISIBLE);
	*objectDefRect_ = Default::createRectFromCenter(getPosition(), BLUE_BOOM_EXPLODE_RANGE);
	EffectManager::addSmallExplode(getPosition());
}

void BlueBoom::deadEffect()
{
	// Do nothing
}
