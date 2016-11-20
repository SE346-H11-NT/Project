#include "StandShooter.h"
#include "Map.h"


StandShooter::StandShooter(T6Vec3 pos)
{
	setBasicProperties();
	position_ = pos;
	*objectDefRect_ = Default::createRectFromBottomCenter(getPosition(), STAND_SHOOTER_BOUND_SIZE);
	Object::loadObjectResource(STAND_SHOOTER_RESOURCE_LINK.c_str(),
		STAND_SHOOTER_RESOURCE_ROWS, STAND_SHOOTER_RESOURCE_COLUMNS, RESOURCE_MT);
}


StandShooter::~StandShooter()
{
}

unsigned int StandShooter::getScore()
{
	return SCORE_STAND_SHOOTER;
}

void StandShooter::draw()
{
	static STAND_SHOOTER_CANON_TRANSLATES;
	static int timeCounter = 0;

	if (currentCanonTranslate > 0)
	{
		timeCounter += Timer::getRoundTime();
		if (timeCounter >= DEFAULT_FRAME_TIME)
		{
			currentCanonTranslate = 0;
			timeCounter = 0;
		}
	}

	((T6_MergedTexture*)*sprites_)->draw(0, getPosition(), DrawCenter::BOTTOMCENTER, scale_);
	((T6_MergedTexture*)*sprites_)->draw(1, getPosition(), DrawCenter::BOTTOMCENTER, scale_, translate[currentCanonTranslate]);
}

void StandShooter::waitUpdate()
{
	if (Default::checkIfBounded(objectDefRect_, &Camera::getViewPort()))
		activate();
}

void StandShooter::activateUpdate()
{
	static int timer = 0;
	timer += Timer::getRoundTime();

	BulletManager::updateIfObjectIsShooted(this, KEY_DESTROYABLE);

	if (timer >= STAND_SHOOTER_SHOOT_DELAY)
	{
		timer = 0;
		instanceShoot();
		currentCanonTranslate = 1;
	}
}

void StandShooter::deadUpdate()
{
}

bool StandShooter::affect(Object* obj, DWORD key)
{
	return Mobs::affect(obj, key);
}

void StandShooter::setBasicProperties()
{
	Object::setBasicProperties();
	ShootObject::setBasicProperties();

	currentBullet_ = BulletType::ENEMY_MACHINE;
	heathPoints_ = STAND_SHOOTER_LIFE_POINTS;
	scale_ = SCALE_FLIP_X;
}

void StandShooter::deadEffect()
{
	EffectManager::addExplode(Default::computeCenter(*objectDefRect_));
}

int StandShooter::computeShootAngle()
{
	// the shooter only shoot 1 direction
	return 180;
}

T6Vec3 StandShooter::computeShootPoint()
{
	T6Vec3 result = getPosition();
	result.x += STAND_SHOOTER_SHOOTPOINT_FIX.x * scale_.x;
	result.y += STAND_SHOOTER_SHOOTPOINT_FIX.y * scale_.y;

	return result;
}

void StandShooter::update()
{
	Mobs::update();
	ShootObject::update();
}

bool StandShooter::isTerminated()
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