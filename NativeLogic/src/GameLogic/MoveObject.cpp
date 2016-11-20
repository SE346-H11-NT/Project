#include "MoveObject.h"
#include "Map.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

void MoveObject::update(double moveTime, T6Rect (*createT6RectFunction)(T6Vec3, Size), Size boundSize, int updateDirect, bool isUpdateScale)
{
	T6Vec3 trueSpeed = TRUE_SPEED(velocity_, (float)moveTime);

	if (isUpdateScale)
	{
		if (trueSpeed.x > 0.0f)	setScale(SCALE_NO); else
			if (trueSpeed.x < 0.0f)	setScale(SCALE_FLIP_X);
	}

	if (updateDirect == UPDATE_X || updateDirect == UPDATE_XY)
		position_.x += trueSpeed.x;

	if (updateDirect == UPDATE_X)
		velocity_.y = SPEED_NO.y;

	if (updateDirect == UPDATE_Y || updateDirect == UPDATE_XY)
		position_.y += trueSpeed.y;

	position_.z += trueSpeed.z;

	*objectDefRect_ = createT6RectFunction(position_, boundSize);

	gravity_(this);
}

void MoveObject::update()
{
}


void MoveObject::gravityYES(MoveObject* object)
{
	object->velocity_.y += TRUE_SPEED(GRAVITY, (float)Timer::getRoundTime());
}


void MoveObject::gravityNO(MoveObject* object)
{
}


void MoveObject::setBasicProperties()
{
	Object::setBasicProperties();
	gravity_ = &gravityYES;
	velocity_ = SPEED_NO;
	fallThrough_ = false;
}



T6Vec3* MoveObject::getVelo()
{
	return &velocity_;
}


void MoveObject::setVelo(T6Vec3 newVelo)
{
	velocity_ = newVelo;
}


void MoveObject::commandJump()
{
	velocity_.y += JUMP_SPEED;
}


vector<CollisEvent*> MoveObject::updateMoveableWithCollision(
	Size boundSize, 
	bool isSwimCollis, 
	int collisLevel, 
	T6Rect(*createRectFunction)(T6Vec3, Size),
	DWORD absoluteUpdate)
{
	detectCurrentCollisEvent(isSwimCollis, collisLevel);

	if (currentCollisEvents_.size() == 0) { // Doesn't touch to any tile.
		this->MoveObject::update(Timer::getRoundTime(), createRectFunction, boundSize, UPDATE_XY);
	}
	else { // If touch
		// Normally update
		int updateDirect = UPDATE_XY;

		if (absoluteUpdate != UPDATE_XY)
		{
			FOR(currentCollisEvents_.size()){

				Tile *tile = dynamic_cast<Tile *>(currentCollisEvents_.at(i)->getTouchedObject());
				if (NULL != tile)
				{
					if (isSwimCollis || (!isSwimCollis && !tile->isWater()))
					{
						if (currentCollisEvents_.at(i)->isIgnored(&ignoredCollisObject_) && fallThrough_)
						{
							currentCollisEvents_.erase(currentCollisEvents_.begin() + i);
							i--;
							continue;
						}

						if (currentCollisEvents_.at(i)->getTime() == 0)
						{ // Hit from prev update

							if (currentCollisEvents_.at(i)->getDirection() == Direction::DOWN && velocity_.y > 0 ||
								currentCollisEvents_.at(i)->getDirection() == Direction::UP && velocity_.y < 0)
								velocity_.y = 0.0F;

							updateDirect = updateDirect & (~currentCollisEvents_.at(i)->getDirection());
						}
					}
				}
			}
		}

			if (currentCollisEvents_.size() == 0)
				this->MoveObject::update(Timer::getRoundTime(), createRectFunction, boundSize, (updateDirect | absoluteUpdate));
			else
			{
				CollisEvent* firstHappenedEvent = CollisEvent::getFirstHappenedEvent(currentCollisEvents_);
				this->MoveObject::update(firstHappenedEvent->getTime() == 0 ?
					Timer::getRoundTime() : firstHappenedEvent->getTime(),
					createRectFunction,
					boundSize, (updateDirect | absoluteUpdate));
		}
	}
	return currentCollisEvents_;
}


void MoveObject::activateFallThrough()
{
	fallThrough_ = true;
	ignoredCollisObject_.clear();

	FOR(currentCollisEvents_.size())
		ignoredCollisObject_.push_back(currentCollisEvents_.at(i)->getTouchedObject());
}


void MoveObject::deactivateFallThrough()
{
	fallThrough_ = false;
	ignoredCollisObject_.clear();
}


vector<CollisEvent*> MoveObject::getCollisEvent()
{
	return currentCollisEvents_;
}


bool MoveObject::isTerminated()
{
	if (Default::checkIfBounded(&getRect(), &Camera::getViewPort()))
		if (getRect().right < Camera::getViewPort().left ||
			getRect().top < Camera::getViewPort().bottom)
			return true;
	return false;
}


void MoveObject::pushCollisEvent(CollisEvent* newCollis)
{
	currentCollisEvents_.push_back(newCollis);
}


void MoveObject::detectCurrentCollisEvent(bool isWaterCollis, int collisLevel)
{
	FOR(currentCollisEvents_.size())
		SAFE_RELEASE(currentCollisEvents_[i]);
	currentCollisEvents_.clear();

	Map::affectedByTiles(this, isWaterCollis, collisLevel);
}
