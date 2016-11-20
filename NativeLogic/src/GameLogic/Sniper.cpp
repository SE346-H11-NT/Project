#include "Sniper.h"



Sniper::Sniper(T6Vec3 position, Object* target)
{
	setBasicProperties();
	AutoAimingObject::setAimingProperties(target, SNIPER_AIMING_MEASURE, position);

	position_ = position;
	currentBullet_ = BulletType::MOBS;
	status_ = SniperShootSubStatus::SNIPER_STRAIGHT;

	Object::loadObjectResource(SniperShootSubStatus::NUM_OF_SNIPER_STATUS, LINK_SNIPER);

	*this->objectDefRect_ = Default::createRectFromCenter(
		position_,
		sprites_[status_]->getFrameSize());

}


Sniper::~Sniper()
{
}

void Sniper::draw()
{
	int sx = GET_SIGN((int)(target_->getPosition().x - getPosition().x));
	sx != 0 ? scale_.x = (float)sx : 0;

	sprites_[status_]->render(
		Timer::getRoundTime(), position_, ANGLE_NO, scale_, TRANSLATE_NO, DrawCenter::BOTTOMCENTER);
}

int Sniper::computeShootAngle()
{
	return aim();
}

T6Vec3 Sniper::computeShootPoint()
{
	T6Vec3 result = position_;

	result.x += scale_.x * sprites_[status_]->getFrameSize().width / 2;

	switch (status_)
	{
	case HIDDEN_SNIPER_STRAIGHT:
		result.y += HS_HEIGHT_FOOT_TO_STRAIGHT_GUN;
		break;

	case HIDDEN_SNIPER_UP45:
		result.y += sprites_[status_]->getFrameSize().height;
		break;

	case HIDDEN_SNIPER_DOWN45:
		result.y += HS_HEIGHT_FOOT_TO_DOWN45_GUN;
		break;

	default:
		break;
	}

	return result;
}

unsigned int Sniper::getScore()
{
	return SCORE_SNIPER;
}

void Sniper::deadEffect()
{
	T6Vec3 effectPos(position_);
	effectPos.y += (float)(sprites_[status_]->getFrameSize().height / 2.0f);

	EffectManager::addSmallExplode(effectPos);
}

void Sniper::setBasicProperties()
{
	ShootObject::setBasicProperties();
	Mobs::setBasicProperties();
	AutoAimingObject::setBasicProperties();
}


void Sniper::activateUpdate()
{
	ShootObject::update();
	checkIfShooted();

	FOR(shootedBullets_.size())
		if (shootedBullets_.at(i) == nullptr || shootedBullets_.at(i)->getPosition() == POSITION_ZERO) {
		shootedBullets_.erase(shootedBullets_.begin() + i);
		i--;
		}

	if (shootedBullets_.size() < SNIPER_MAX_BULLET_IN_A_ROW)
	{
		Bullet* shootedOne = shoot();
		if (shootedOne != nullptr)
			shootedBullets_.push_back(shootedOne);
	}

	status_ = (currentAimingAngle_ % 180 == 0 ? 0 : (1 + currentAimingAngle_ / 180));
}

void Sniper::waitUpdate()
{
	if (Default::computeDistance(target_->getPosition(), position_) <= SNIPER_SHOOT_DISTANCE)
		activate();
}

void Sniper::deadUpdate()
{
}


void Sniper::update()
{
	Mobs::update();
}


bool Sniper::affect(Object* obj, DWORD key)
{
	return Mobs::affect(obj, key);
}

bool Sniper::isTerminated()
{
	return Mobs::isTerminated();
}
