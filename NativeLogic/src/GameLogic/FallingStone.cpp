#include "FallingStone.h"

T6Vec2 FallingStone::translate_ = ROLLING_TRANSLATE;

FallingStone::FallingStone(T6Vec3 position)
{
	setBasicProperties();
	respawPos_ = position_ = position;
	*objectDefRect_ = Default::createRectFromCenter(position_, FALLING_STONE_BOUND_SIZE);
	Object::loadObjectResource(FALLING_STONE_RESOURCE_LINK.c_str(), 
								FALLING_STONE_RESOURCE_ROWS, 
								FALLING_STONE_RESOURCE_COLUMNS, 
								RESOURCE_MS);
}


FallingStone::~FallingStone()
{
}

unsigned int FallingStone::getScore()
{
	return SCORE_FALLING_STONE;
}

void FallingStone::draw()
{
	if (!isDead())
		if (status_ == FALLING_STONE_ROOL)
			(*sprites_)->render(Timer::getRoundTime(), position_, ANGLE_NO, SCALE_NO, translate_, DrawCenter::CENTER);
		else
			(*sprites_)->render(Timer::getRoundTime(), position_, ANGLE_NO, scale_, TRANSLATE_NO, DrawCenter::CENTER);
}

void FallingStone::waitUpdate()
{
	if (Default::checkIfBounded(objectDefRect_, &Camera::getViewPort()))
		activate();
}

void FallingStone::activateUpdate()
{
	static int currentFlip = 0;
	static int currentTimeSign = 0;
	static DWORD frameTime_;
	static SCALE_CASE;

	timeCounter_ += Timer::getRoundTime();

	scale_ = scale[currentFlip];

	if (currentTimeSign != Timer::getRoundCode())
	{
		currentTimeSign = Timer::getRoundCode();
		frameTime_ += Timer::getRoundTime();
		if (frameTime_ >= FALLING_STONE_FRAME_TIME)
		{
			frameTime_ = 0;
			currentFlip = (currentFlip + 1) % NUM_OF_SCALE_CASE;
			translate_ = translate_.getInvert();
		}
	}

	switch (status_)
	{
	case FALLING_STONE_ROOL:
		if (timeCounter_ >= FALLING_STONE_ROLL_TIME)
		{
			timeCounter_ = 0;
			status_ = FALLING_STONE_FALL;
			Object::activate(PROPERTIES_VISIBLE);
		}
		break;

	case FALLING_STONE_FALL:

		if (!currentCollisEvents_.empty())
		{
			activateFallThrough();
			commandJump();
		}

		updateMoveableWithCollision(FALLING_STONE_BOUND_SIZE, false, TileType::TOP_ONLY, &Default::createRectFromCenter);
		BulletManager::updateIfObjectIsShooted(this, KEY_DESTROYABLE);

		if (position_.y < Camera::getViewPort().bottom)
		{
			dead(0);
			deactivate(PROPERTIES_VISIBLE);
		}
		break;

	default:
		break;
	}
}

void FallingStone::deadUpdate()
{
	timeCounter_ += Timer::getRoundTime();
	if (timeCounter_ >= FALLING_STONE_RELOAD_TIME)
	{
		activate();
		timeCounter_ = 0;
		reset();
	}
}

void FallingStone::setBasicProperties()
{
	MoveObject::setBasicProperties();
	Mobs::setBasicProperties();
	setVelo(SPEED_NO);
	deactivate(PROPERTIES_VISIBLE);
	status_ = FALLING_STONE_ROOL;
	heathPoints_ = FALLING_STONE_HEALTH_POINTS;
}

void FallingStone::deadEffect()
{
	EffectManager::addExplode(position_);
}

bool FallingStone::isDead()
{
	return (position_.y < Camera::getViewPort().bottom && !Default::checkIfBounded(objectDefRect_, &Camera::getViewPort()) ||
		Mobs::isDead());
}

void FallingStone::update()
{
	Mobs::update();
}

bool FallingStone::affect(Object* obj, DWORD key)
{
	return Mobs::affect(obj, key);
}

bool FallingStone::isTerminated()
{
	return (respawPos_.y < Camera::getViewPort().bottom);
}

void FallingStone::commandJump()
{
	setVelo(FALLING_STONE_JUMP_VELO);
}


void FallingStone::reset()
{
	status_ = FALLING_STONE_ROOL;
	position_ = respawPos_;
	timeCounter_ = 0;
	setVelo(SPEED_NO);
	heathPoints_ = FALLING_STONE_HEALTH_POINTS;
	ignoredCollisObject_.clear();
}
