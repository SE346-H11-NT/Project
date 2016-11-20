#include "RunningMan.h"
#include "BulletManager.h"
#include "Map.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif


RunningMan::RunningMan(T6Vec3 position, Velocity velocity, int numOfBullet)
{
	setBasicProperties();
	this->position_ = position;
	this->respawPosition_ = position;
	Object::loadObjectResource(RunningManStatus::NUM_OF_RM_STATUS, LINK_RUNNING_MAN);

	*this->objectDefRect_ = Default::createRectFromBottomCenter(
		position_,
		sprites_[RunningManStatus::RUNNING_MAN_RUN]->getFrameSize());

	this->mobState_ = MobState::MOBS_STATE_WAIT;
	this->velocity_ = velocity;
	this->respawnTime_ = RUNNING_MAN_RESPAWN_TIME;
	this->bulletPool_ = numOfBullet;
}


RunningMan::~RunningMan()
{
}


void RunningMan::activateUpdate()
{
	switch (status_)
	{
	case RUNNING_MAN_RUN:
	{
		updateMoveableWithCollision();
		checkIfShooted();

		if (nextStepIsNotLand() && status_ == RUNNING_MAN_RUN) {
			srand((unsigned int)time(NULL));
			if (rand() % 2 == 0) {
				velocity_.x = -velocity_.x;
			}
			else {
				commandJump();
			}
		}

		if (shootedBullet_ < bulletPool_)
		{
			shootTime_ += Timer::getRoundTime();

			if (shootTime_ >= RUNNING_MAN_RELOAD_TIME)
			{
				status_ = RunningManStatus::RUNNING_MAN_SHOOT;
				shootTime_ = 0;
			}
		}
		break;
	}

	case RUNNING_MAN_JUMP:
		checkIfShooted();

		if (updateMoveableWithCollision().size() > 0)
			status_ = RunningManStatus::RUNNING_MAN_RUN;

		break;

	case RUNNING_MAN_SHOOT:
		checkIfShooted();

		if ((shootTime_ % RUNNING_MAN_SHOOT_DELAY) <= Timer::getRoundTime() && shootTime_ < bulletPool_)
		{
			static RELOAD_TIME;
			lastShootTime_ = reload[(currentBullet_)];
			shoot();
			shootedBullet_++;
		}

		if (shootTime_ > RUNNING_MAN_SHOOT_TIME(bulletPool_))
		{
			shootedBullet_ = 0;
			status_ = RUNNING_MAN_RUN;
			shootTime_ = 0;
		}

		shootTime_ += Timer::getRoundTime();

		break;
	default:
		break;
	}

	if (!Default::checkIfPointInRect(position_, Default::multipleRectWithDouble(Camera::getViewPort(), 1.2)))
		suspend();
}


unsigned int RunningMan::getScore()
{
	return SCORE_RUNNING_MAN;
}


void RunningMan::draw()
{
	if (status_ >= RunningManStatus::RUNNING_MAN_RUN && isActivated())
		sprites_[status_]->render(Timer::getRoundTime(), position_, 0, getScale(), TRANSLATE_NO, DrawCenter::BOTTOMCENTER);
}


void RunningMan::deadEffect()
{
	T6Vec3 effectPos(position_);
	effectPos.y += (float)(sprites_[status_]->getFrameSize().height / 2.0f);

	EffectManager::addSmallExplode(effectPos);

	suspend();
}


bool RunningMan::nextStepIsNotLand()
{
	FOR(currentCollisEvents_.size())
	{
		if (currentCollisEvents_.at(i)->getDirection() == Direction::UP)
			if ((currentCollisEvents_.at(i)->getTouchedObject()->getRect().left > position_.x && getVelo()->x < 0) ||
				(currentCollisEvents_.at(i)->getTouchedObject()->getRect().right < position_.x && getVelo()->x > 0))
			{
			if (!dynamic_cast<Tile*>(currentCollisEvents_.at(i)->getTouchedObject())->isWater())
				FORJ(currentCollisEvents_.size())
			{
				if (currentCollisEvents_.at(j)->getDirection() == Direction::UP)
					if (currentCollisEvents_.at(i)->getTouchedObject()->getRect().left ==
						currentCollisEvents_.at(j)->getTouchedObject()->getRect().right ||
						currentCollisEvents_.at(i)->getTouchedObject()->getRect().right ==
						currentCollisEvents_.at(j)->getTouchedObject()->getRect().left)
						goto CONTINUE;
			}
			return true;
			}
	CONTINUE:;
	}
	return false;
}


void RunningMan::commandJump()
{
	sprites_[status_]->reset();
	status_ = RunningManStatus::RUNNING_MAN_JUMP;
	velocity_.y += RUNNING_MAN_JUMP_SPEED;
}

vector<CollisEvent*> RunningMan::updateMoveableWithCollision()
{
	MoveObject::updateMoveableWithCollision(RUNNING_MAN_BOUND_SIZE);

	if (currentCollisEvents_.size() > 0)
	{
		FOR(currentCollisEvents_.size())
			if (!dynamic_cast<Tile*>(currentCollisEvents_.at(i)->getTouchedObject())->isWater())
				return currentCollisEvents_;

		EffectManager::addWaterFlow(position_);
		suspend();
	}

	return currentCollisEvents_;
}


void RunningMan::setBasicProperties()
{
	MoveObject::setBasicProperties();
	Mobs::setBasicProperties();
	ShootObject::setBasicProperties();
	currentBullet_ = BulletType::MOBS;
}

void RunningMan::waitUpdate()
{
	if (respawnTime_ >= RUNNING_MAN_RESPAWN_TIME)
	{
		if (!Default::checkIfPointInRect(respawPosition_, Camera::getViewPort()) &&
			Default::checkIfPointInRect(respawPosition_, Default::multipleRectWithDouble(Camera::getViewPort(), 1.2)))
			if (respawPosition_.x > Camera::getViewPort().left - 50)
			{
			activate();
			respawnTime_ = 0;
			shootTime_ = 0;
			}
			else
				Mobs::compulsoryDead();
	}
	else
	{
		respawnTime_ += Timer::getRoundTime();
	}
}

void RunningMan::deadUpdate()
{
	suspend();
}


void RunningMan::activate()
{
	Mobs::activate();
	Object::deactivate(PROPERTIES_EVATION);

	status_ = RunningManStatus::RUNNING_MAN_RUN;
	position_ = respawPosition_;
	*objectDefRect_ = Default::createRectFromBottomCenter(position_, RUNNING_MAN_BOUND_SIZE);
	velocity_.x = fabs(velocity_.x) * GET_SIGN(Camera::getPosition().x - respawPosition_.x);
}

bool RunningMan::affect(Object* obj, DWORD key)
{
	return Mobs::affect(obj, key);
}


void RunningMan::update()
{
	Mobs::update();
}

bool RunningMan::isTerminated()
{
	return (Mobs::isTerminated() && MoveObject::isTerminated());
}


void RunningMan::suspend()
{
	Mobs::suspend();

	Object::activate(PROPERTIES_EVATION);
	heathPoints_ = 1;
	position_ = respawPosition_;
}


int RunningMan::computeShootAngle()
{
	return (scale_.x > 0 ? RUNNING_MAN_SHOOT_ANGLE_RIGHT : RUNNING_MAN_SHOOT_ANGLE_LEFT);
}


T6Vec3 RunningMan::computeShootPoint()
{
	return (position_ + RUNNING_MAN_SHOOT_POINT_DISTANCE_FROM_POSITION(scale_.x));
}