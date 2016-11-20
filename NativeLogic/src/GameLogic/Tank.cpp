#include "Tank.h"
#include "Map.h"

Tank::Tank(T6Vec3 pos, Object* target)
{
	setBasicProperties();
	position_ = pos;
	*objectDefRect_ = Default::createRectFromBottomCenter(pos, TANK_BOUND_SIZE);
	Object::loadObjectResource(TANK_RESOURCE_LINK.c_str(), TANK_RESOURCE_ROWS, TANK_RESOURCE_COLUMNS, RESOURCE_MT);
	gun_ = new TankGun(pos + TANK_GUN_POS_FIX(scale_.x), this, target);
}


Tank::~Tank()
{
	SAFE_RELEASE(gun_);
}

unsigned int Tank::getScore()
{
	return SCORE_TANK;
}

void Tank::draw()
{
	static TANK_FADE_COLORS;
	int fadeColorIndex = (int)((heathPoints_ - 1) / (TANK_LIFE_POINTS / TANK_NUM_OF_COLORS));
	((T6_MergedTexture*)*sprites_)->draw(drawIndex_ * 2 + 0, getPosition(), DrawCenter::BOTTOMCENTER, scale_);
	((T6_MergedTexture*)*sprites_)->draw(drawIndex_ * 2 + 1, getPosition(), DrawCenter::BOTTOMCENTER, scale_,
		TRANSLATE_NO, ANGLE_NO, colors[fadeColorIndex]);

	gun_->setColor(colors[fadeColorIndex]);
	gun_->draw();
}

void Tank::waitUpdate()
{
	if (Default::checkIfBounded(this->objectDefRect_, &Camera::getViewPort()))
		activate();
}

void Tank::activateUpdate()
{
	BulletManager::updateIfObjectIsShooted(this, KEY_DESTROYABLE);
	switch (status_)
	{
	case TANK_MOVE:
	{
		static int frameTime = 0;
		frameTime += Timer::getRoundTime();
		if (frameTime >= DEFAULT_FRAME_TIME)
		{
			drawIndex_ = (drawIndex_ == 0 ? 1 : 0);
		}

		if (timeCounter_ > Timer::getRoundTime())
		{
			MoveObject::updateMoveableWithCollision(TANK_BOUND_SIZE);
		}
		else
		{
			timeCounter_ = TANK_STAND_TIME;
			status_ = TANK_STAND;
			setVelo(SPEED_NO);
			gun_->activate();
		}
		break;
	}

	case TANK_STAND:
		if (timeCounter_ < Timer::getRoundTime())
		{
			status_ = TANK_MOVE;
			timeCounter_ = -1; // move for infinity
			setVelo(TANK_MOVE_SPEED(scale_.x));
		}
		break;

	default:
		break;
	}

	gun_->update();
	timeCounter_ -= Timer::getRoundTime();
}

void Tank::deadUpdate()
{
}

bool Tank::affect(Object* obj, DWORD key)
{
	return Mobs::affect(obj, key);
}

void Tank::setBasicProperties()
{
	Mobs::setBasicProperties();
	MoveObject::setBasicProperties();

	scale_ = SCALE_FLIP_X;
	drawIndex_ = 0;
	status_ = TANK_MOVE;
	setVelo(TANK_MOVE_SPEED(scale_.x));
	timeCounter_ = TANK_MOVE_TIME;
	heathPoints_ = TANK_LIFE_POINTS;
}

void Tank::deadEffect()
{
	srand((unsigned int)time(nullptr));

	FOR(10)
	{
		T6Vec3 explopos = getPosition();
		explopos.y += (rand() % (int)TANK_BOUND_SIZE.height);
		explopos.x += (rand() % (int)TANK_BOUND_SIZE.width) - ((int)TANK_BOUND_SIZE.width / 2);

		EffectManager::addExplode(explopos, i * DEFAULT_FRAME_TIME);
	}
}

void Tank::update()
{
	Mobs::update();
}

bool Tank::isTerminated()
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
