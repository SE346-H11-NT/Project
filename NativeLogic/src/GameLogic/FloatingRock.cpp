#include "FloatingRock.h"


FloatingRock::FloatingRock(T6Vec3 position, T6Vec3 velocity, T6Rect moveRange)
{
	setBasicProperties();
	position_ = position;
	setVelo(velocity);
	moveRange_ = moveRange;
	Object::loadObjectResource(FLOATING_ROCK_RESOURCE_LINK.c_str(), FLOATING_ROCK_RESOURCE_ROWS, FLOATING_ROCK_RESOURCE_COLUMNS, RESOURCE_MS);
	*objectDefRect_ = Default::createRectFromCenter(position_, FLOATING_ROCK_BOUND_SIZE);
}


FloatingRock::~FloatingRock()
{
}

void FloatingRock::update()
{
	MoveObject::update(Timer::getRoundTime(), Default::createRectFromCenter, FLOATING_ROCK_BOUND_SIZE, UPDATE_X, false);

	if (objectDefRect_->left < moveRange_.left ||
		objectDefRect_->right > moveRange_.right)
	{
		setVelo(T6Vec3(-getVelo()->x, getVelo()->y, getVelo()->z));
	}
}

void FloatingRock::draw()
{
	(*sprites_)->render(Timer::getRoundTime(), position_, ANGLE_NO, scale_, TRANSLATE_NO, DrawCenter::CENTER);
}

void FloatingRock::setBasicProperties()
{
	MoveObject::setBasicProperties();
	Tile::setBasicProperties();
	gravity_ = gravityNO;
}

bool FloatingRock::affect(Object* obj, DWORD key)
{
	affect(obj, key, TileType::TOP_ONLY);
	return false;
}

bool FloatingRock::affect(Object* obj, DWORD key, TileType collisLevel)
{
	if (Tile::affect(obj, key, collisLevel))
		obj->fixPosition(TRUE_SPEED(*getVelo(), Timer::getRoundTime()));
	return false;
}

bool FloatingRock::isTerminated()
{
	return MoveObject::isTerminated();
}

T6Vec3* FloatingRock::getVelo()
{
	return MoveObject::getVelo();
}
