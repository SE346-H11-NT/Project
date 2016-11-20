#include "Tile.h"
#include "Character.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif


Tile::Tile(long left, long right, long top, long bottom, int characterTouch, TileType type)
{
	Object::setBasicProperties();
	currentTouchableStatus_ = Object::propertiesYes;
	currentShootableStatus_ = Object::propertiesNo;

	type_ = type;
	characterTouch_ = characterTouch;

	*objectDefRect_ = Default::createT6Rect(left, right, top, bottom);
	this->position_ = Default::computeCenter(*objectDefRect_);
}

Tile::Tile()
{

}


Tile::~Tile()
{
	FOR(linkedPretties_.size())
		SAFE_RELEASE(linkedPretties_.at(i));
	linkedPretties_.clear();
}


void Tile::draw()
{
	FOR(linkedPretties_.size())
		linkedPretties_.at(i)->draw();
}


void Tile::update()
{
}


TileType Tile::getType()
{
	return type_;
}


int Tile::getTouchedStatus()
{
	return characterTouch_;
}


T6Rect Tile::getRect()
{
	return *objectDefRect_;
}


void Tile::pushAPretties(Pretties* newPretties)
{
	linkedPretties_.push_back(newPretties);
}


void Tile::activate()
{

}


bool Tile::isWater()
{
	return (characterTouch_ == CharacterStatus::SWIM);
}

void Tile::setBasicProperties()
{
	Object::setBasicProperties();
	characterTouch_ = 0;
}

bool Tile::affect(Object* obj, DWORD key, TileType collisLevel)
{
	if ((this->isWater() && !CHECK_KEY(key, KEY_WATER_COLLIS)) || type_ < collisLevel)
		return false;

	if (CHECK_KEY(key, KEY_MOVEABLE))
	{
		double time = 0;
		Direction direct = Direction::NONE;

		if (isTouchable())
			time = Collision::checkCollision(obj, this, &direct);

		if (direct != Direction::NONE) { // If the object touched this tile.
			if (getType() >= TouchLevel::FOUR_FACE || direct == Direction::UP) // If tile is touchable at any direction or the touch side is top of tile
				if (time <= Timer::getRoundTime() && time >= 0) // If this collision happened sooner than current result, replace it, then.
				{
				if (time == 0)
				{
					switch (direct)
					{
					case UP:	if (obj->getRect().bottom < this->getRect().top)	return false; break;
					case DOWN:	if (obj->getRect().top > this->getRect().bottom)	return false; break;
					case LEFT:	if (obj->getRect().right > this->getRect().left)	return false; break;
					case RIGHT:	if (obj->getRect().left < this->getRect().right)	return false; break;
					default: break;
					}
				}

				MoveObject *moveObject = dynamic_cast<MoveObject *>(obj);
				moveObject->pushCollisEvent(new CollisEvent(this, direct, time));
				return true;
				}
		}
	}

	return false;
}


bool Tile::affect(Object* obj, DWORD key)
{
	return affect(obj, key, TileType::TOP_ONLY);
}


bool Tile::isTerminated()
{
	return false;
}
