#include "BoomingCanon.h"


BoomingCanon::BoomingCanon(T6Vec3 position, bool drawGuards, DWORD countedTime)
{
	setBasicProperties();
	position_ = position;
	*objectDefRect_ = Default::createRectFromDrawCenter(position_, BOOMING_CANON_BOUND_SIZE, DrawCenter::TOPRIGHT);
	Object::loadObjectResource(BOOMING_CANON_RESOURCE_LINK.c_str(),
		BOOMING_CANON_RESOURCE_ROWS,
		BOOMING_CANON_RESOURCE_COLUMNS,
		RESOURCE_MT);

	isDrawGuards_ = drawGuards;
	timeCounter_ = countedTime;
}


BoomingCanon::~BoomingCanon()
{
}

unsigned int BoomingCanon::getScore()
{
	return SCORE_BOOMING_CANON;
}

void BoomingCanon::draw()
{
	if (!isDead())
	{
		((T6_MergedTexture*)*sprites_)->draw(0, position_, status_ == BCS_READY_TO_SHOOT ? 0.8F : 1.0F, 1.0F, true, DrawCenter::TOPRIGHT);
		if (isDrawGuards_)
			((T6_MergedTexture*)*sprites_)->draw(1, position_, DrawCenter::TOPRIGHT, SCALE_NO, BOOMING_CANON_GUARD_TRANSLATE);
	}
}

void BoomingCanon::waitUpdate()
{
	if (Default::checkIfBounded(objectDefRect_, &Camera::getViewPort()))
	{
		activate();
	}
}

void BoomingCanon::activateUpdate()
{
	BulletManager::updateIfObjectIsShooted(this, KEY_DESTROYABLE);
	ShootObject::update();

	if (stateProcess())
		shoot(computeBulletLauchVelo());
}

void BoomingCanon::deadUpdate()
{
}

void BoomingCanon::deadEffect()
{
	EffectManager::addExplode(Default::computeCenter(*objectDefRect_));
}

void BoomingCanon::setBasicProperties()
{
	ShootObject::setBasicProperties();
	Mobs::setBasicProperties();
	shootedBullet_ = nullptr;
	isDrawGuards_ = false;
	status_ = BoomingCanonState::BCS_RELOAD;
	currentBullet_ = BulletType::RED_BOOM;
	heathPoints_ = BOOMING_CANON_HEALTH_POINTS;
}

int BoomingCanon::computeShootAngle()
{
	return 0;
}

T6Vec3 BoomingCanon::computeShootPoint()
{
	T6Vec3 result;
	result.x = position_.x - (*sprites_)->getFrameSize().width;
	result.y = position_.y - (*sprites_)->getFrameSize().height / 2.0F;
	result.z = DEFAULT_DEPTH;

	return result;
}

void BoomingCanon::update()
{
	Mobs::update();
}

bool BoomingCanon::affect(Object* obj, DWORD key)
{
	Mobs::affect(obj, key);
	return false;
}

bool BoomingCanon::isTerminated()
{
	return isDead();
}


bool BoomingCanon::stateProcess()
{
	timeCounter_ += Timer::getRoundTime();

	DWORD stateTime;

	switch (status_)
	{
	case BCS_RELOAD:
		stateTime = BOOMING_CANON_SHOOT_STATE_TIME * 2;
		break;

	case BCS_SHOOT:
	case BCS_READY_TO_SHOOT:
		stateTime = BOOMING_CANON_SHOOT_STATE_TIME;
		break;

	default:
		break;
	}

	if (timeCounter_ >= stateTime)
	{
		timeCounter_ = 0;
		status_ = (status_ + 1) % BoomingCanonState::NUM_OF_BCS_STATE;

		if (status_ == BoomingCanonState::BCS_SHOOT)
			return true;
	}

	return false;
}


T6Vec3 BoomingCanon::computeBulletLauchVelo()
{
	// L = v * sqrt(2 * h / g)
	// L: how far the bullet can reach
	// v: the very start velocity
	// h: height
	// g: gravity

	static int fireForces[] = { 32, 96, 160, 224 };

	srand((unsigned int)time(nullptr));

	return SPEED_X(-fireForces[rand() % 4]);
}