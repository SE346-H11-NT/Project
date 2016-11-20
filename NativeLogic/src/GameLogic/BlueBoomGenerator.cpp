#include "BlueBoomGenerator.h"


BlueBoomGenerator::BlueBoomGenerator(T6Vec3 pos)
{
	position_ = pos;
}


BlueBoomGenerator::~BlueBoomGenerator()
{
}

void BlueBoomGenerator::setBasicProperties()
{
	Object::setBasicProperties();
}

void BlueBoomGenerator::update()
{
	if (timeCounter_ < BB_GENERATOR_DELAY)
	{
		timeCounter_ += Timer::getRoundTime();
	}

	if (Default::checkIfPointInRect(getPosition(), Camera::getViewPort()))
	{
		if (timeCounter_ >= BB_GENERATOR_DELAY)
		{
			Map::addGameObject(new BlueBoom(getPosition()));
			timeCounter_ = 0;
		}
	}
}

void BlueBoomGenerator::draw()
{
	// Do nothing
}

bool BlueBoomGenerator::affect(Object* obj, DWORD key)
{
	// Do nothing
	return false;
}

bool BlueBoomGenerator::isTerminated()
{
	return (getPosition().x < Camera::getViewPort().left);
}
