#include "DiveShooter.h"


DiveShooter::DiveShooter(T6Vec3 position, Object* target)
{
	setBasicProperties();
	position_ = position;
	target_ = target;
	Object::loadObjectResource(
		DIVE_SHOOTER_RESOURCE_LINK.c_str(), 
		DIVE_SHOOTER_RESOURCE_ROWS,
		DIVE_SHOOTER_RESOURCE_COLUMNS,
		RESOURCE_MT);
	*objectDefRect_ = Default::createRectFromBottomCenter(position_, DIVE_SHOOTER_BOUND_SIZE);
}


DiveShooter::~DiveShooter()
{
}

unsigned int DiveShooter::getScore()
{
	return SCORE_DIVE_SHOOTER;
}

void DiveShooter::draw()
{
	if (!isDead())
	{
		((T6_MergedTexture*)(*sprites_))->draw(status_, position_, DrawCenter::BOTTOMCENTER, SCALE_NO, translate_);
	}
}

void DiveShooter::waitUpdate()
{
	if (Default::checkIfPointInRect(getPosition(), Camera::getViewPort()) && 
		target_->getPosition().y > (getPosition().y + DIVE_SHOOTER_GOOD_DISTANCE_TO_TARGET_Y))
	{
		activate();
	}
}

void DiveShooter::activateUpdate()
{
	timer_ += Timer::getRoundTime();

	switch (status_)
	{
	case DiveShooterState::DIVE_SHOOTER_DIVING:
		if (timer_ >= DIVE_SHOOTER_RELOAD_TIME)
		{
			timer_ = 0;
			status_ = DiveShooterState::DIVE_SHOOTER_SHOOT;
		}
		break;

	case DiveShooterState::DIVE_SHOOTER_SHOOT:

		BulletManager::updateIfObjectIsShooted(this, KEY_NO);

		if (timer_ >= DEFAULT_FRAME_TIME && timer_ - Timer::getRoundTime() < DEFAULT_FRAME_TIME)
		{
			RedSpreadBoom* bullet = reinterpret_cast<RedSpreadBoom*>(shoot());
			bullet->assignTarget(target_);
		}

		if (timer_ >= DIVE_SHOOTER_SHOOT_TIME)
		{
			timer_ = 0;
			status_ = DiveShooterState::DIVE_SHOOTER_DIVING;
		}
		break;

	default:
		break;
	}
}

void DiveShooter::deadUpdate()
{
}

bool DiveShooter::affect(Object* obj, DWORD key)
{
	return Mobs::affect(obj, key);
}

void DiveShooter::setBasicProperties()
{
	Mobs::setBasicProperties();
	ShootObject::setBasicProperties();
	translate_ = T6Vec2(0.0F, 1.0F);
	currentBullet_ = BulletType::RED_SPREAD_BOOM;
}

void DiveShooter::deadEffect()
{
	EffectManager::addSmallExplode(position_);
}

bool DiveShooter::isDead()
{
	return Mobs::isDead();
}

void DiveShooter::update()
{
	Mobs::update();
	ShootObject::update();
	computeTranslate();
}

bool DiveShooter::isTerminated()
{
	return (isDead() || 
			(!Default::checkIfBounded(objectDefRect_, &Camera::getViewPort()) &&
			(position_.x < Camera::getViewPort().left ||
			position_.y < Camera::getViewPort().bottom)));
}

int DiveShooter::computeShootAngle()
{
	return ANGLE_COUNTER_CLOCKWISE(90);
}

T6Vec3 DiveShooter::computeShootPoint()
{
	return (position_ + DIVE_SHOOTER_SHOOTPOINT_DISTANCE_FROM_POSITION);
}


void DiveShooter::computeTranslate()
{
	frameTime_ += Timer::getRoundTime();

	if (frameTime_ >= DIVE_SHOOTER_FRAME_TIME)
	{
		translate_.y = -translate_.y;
		frameTime_ = 0;
	}
}