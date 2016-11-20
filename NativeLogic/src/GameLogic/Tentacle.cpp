#include "Tentacle.h"


Tentacle::Tentacle(T6Vec3 position, int angleInDegree, Object* target)
{
	setBasicProperties();
	FOR(TENTACLE_NUM_OF_METAL_ORB)
	{
		orbs_.push_back(new TOrb(new MetalOrb(position), angleInDegree, i * TENTACLE_ORB_PREPARE_TIME));
	}

	head_ = new CrystalOrb(position, target);
	target_ = target;
	orbs_.push_back(new TOrb(head_, angleInDegree, TENTACLE_ORB_PREPARE_TIME * orbs_.size()));
	headDirection_ = angleInDegree;

	if (Default::fixAngle(angleInDegree) > ANGLE_COUNTER_CLOCKWISE(90) &&
		Default::fixAngle(angleInDegree) < ANGLE_COUNTER_CLOCKWISE(270))
	{
		waveSpeedProcess_ = &Tentacle::waveSpeedProcessLeft;
		routSpeed_ = TENTACLE_WAVE_SPEED;
	}
	else
	{
		waveSpeedProcess_ = &Tentacle::waveSpeedProcessRight;
		routSpeed_ = -TENTACLE_WAVE_SPEED;
	}
}


Tentacle::~Tentacle()
{
	FOR(orbs_.size())
		SAFE_RELEASE(orbs_.at(i));
	orbs_.clear();
}

unsigned int Tentacle::getScore()
{
	return SCORE_TENTACLE;
}

void Tentacle::draw()
{
	if (isActivated_)
	{
		FOR(orbs_.size())
			orbs_.at(i)->orb->draw();
	}
	else
	{
		FOR(orbs_.size())
			if (orbs_.at(i)->orb->getPosition() != orbs_.at(0)->orb->getPosition())
				orbs_.at(i)->orb->draw();
	}
}

void Tentacle::activateUpdate()
{
	if (isActivated_)
	{
		preparingTimeProcess();
		static updateFunc updateFunctions[] = { &Tentacle::updateWaveType, &Tentacle::updateRoundType, &Tentacle::updatePointType };

		if ((this->*(updateFunctions[currentUpdatefunction_]))())
		{
			timerCounter_ = 0;
			currentUpdatefunction_ = (currentUpdatefunction_ + 1) % TENTACLE_NUM_OF_UPDATE_TYPE;
		}

		FOR(orbs_.size())
			orbs_.at(i)->orb->update();
	}
	else
	{
		activating();
	}
}

void Tentacle::deadUpdate()
{
	FOR(orbs_.size())
		orbs_.at(i)->orb->damaged(BULLET_DAMAGE_MASSIVE);
}

void Tentacle::setBasicProperties()
{
	Mobs::setBasicProperties();
	deactivate(PROPERTIES_VISIBLE);
	Object::activate(PROPERTIES_EVATION);
	timerCounter_ = 0;
	waveSpeed_ = TENTACLE_WAVE_SPEED;
	currentUpdatefunction_ = 0;
	heathPoints_ = TENTACLE_LIFE_POINT;
}

bool Tentacle::affect(Object* obj, DWORD key)
{
	return head_->affect(obj, key);
}

bool Tentacle::isTerminated()
{
	return head_->isTerminated();
}

bool Tentacle::isDead()
{
	return head_->isDead();
}

bool Tentacle::updateWaveType()
{
	(this->*(this->waveSpeedProcess_))();

	orbs_.at(0)->angle += TRUE_SPEED(waveSpeed_, Timer::getRoundTime());

	DFOR(orbs_.size() - 1)
		if (i > 0)
			orbs_.at(i)->angle = orbs_[i - 1]->angle;

	setOrbPosByTheirAngle();
	
	timerCounter_ += Timer::getRoundTime();
	return (timerCounter_ >= TENTACLE_UPDATE_TURN_TIME);
}

bool Tentacle::updateRoundType()
{
	orbs_.at(0)->angle += TRUE_SPEED(routSpeed_, Timer::getRoundTime());

	DFOR(orbs_.size() - 1)
		if (i > 0)
		orbs_.at(i)->angle = orbs_[i - 1]->angle;

	//headDirection_ += TRUE_SPEED(routSpeed_, Timer::getRoundTime());

	setOrbPosByTheirAngle();

	timerCounter_ += Timer::getRoundTime();
	return (timerCounter_ >= TENTACLE_UPDATE_TURN_TIME);
}

bool Tentacle::updatePointType()
{
	double angleToTarget = CircleEquation(orbs_.at(0)->orb->getPosition(), target_->getPosition()).
		getDegreeFromCoodirate(target_->getPosition());

	headDirection_ = RADIAN_TO_DEGREE(angleToTarget);

	FOR(orbs_.size())
		orbs_.at(i)->angle = angleToTarget;

	setOrbPosByTheirAngle();

	timerCounter_ += Timer::getRoundTime();
	return (timerCounter_ >= TENTACLE_UPDATE_TURN_TIME);
}

void Tentacle::waveSpeedProcessLeft()
{
	double rootAngle = CircleEquation(orbs_.at(0)->orb->getPosition(),
		orbs_.at(1)->orb->getPosition()).getDegreeFromCoodirate(orbs_.at(1)->orb->getPosition());

	if (Default::fixAngle(rootAngle) >= ANGLE_COUNTER_CLOCKWISE(225))
		waveSpeed_ = -TENTACLE_WAVE_SPEED;
	else if (Default::fixAngle(rootAngle) <= ANGLE_COUNTER_CLOCKWISE(135))
		waveSpeed_ = TENTACLE_WAVE_SPEED;
}

void Tentacle::waveSpeedProcessRight()
{
	double rootAngle = CircleEquation(orbs_.at(0)->orb->getPosition(),
		orbs_.at(1)->orb->getPosition()).getDegreeFromCoodirate(orbs_.at(1)->orb->getPosition());

	if (rootAngle >= ANGLE_COUNTER_CLOCKWISE(45))
		waveSpeed_ = -TENTACLE_WAVE_SPEED;
	else if (rootAngle <= ANGLE_CLOCKWISE(45))
		waveSpeed_ = TENTACLE_WAVE_SPEED;
}

void Tentacle::activating()
{
	double moveCap = TENTACLE_ORB_DISTANCE -
		Default::computeDistance(orbs_.at(0)->orb->getPosition(), orbs_.at(1)->orb->getPosition());

	T6Vec3 moveDistance;
	if (moveCap < TRUE_SPEED(TENTACLE_ACTIVATE_SPEED, Timer::getRoundTime()))
	{
		moveDistance = T6Vec3(
			Default::cos(DEGREE_TO_RADIAN(headDirection_)) * moveCap,
			Default::sin(DEGREE_TO_RADIAN(headDirection_)) * moveCap,
			0.0F);
		isActivated_ = true;
	}
	else
		moveDistance = TRUE_SPEED(T6Vec3(
		Default::cos(DEGREE_TO_RADIAN(headDirection_)) * TENTACLE_ACTIVATE_SPEED,
		Default::sin(DEGREE_TO_RADIAN(headDirection_)) * TENTACLE_ACTIVATE_SPEED,
		0.0F),
		Timer::getRoundTime());
	
	DFOR(orbs_.size() - 1)
	{
		if (i > 0)
		{
			orbs_.at(i)->orb->setPos(orbs_.at(i)->orb->getPosition() + moveDistance);

			if (Default::computeDistance(orbs_.at(i - 1)->orb->getPosition(), orbs_.at(i)->orb->getPosition()) <
				TENTACLE_ORB_DISTANCE)
				return;
		}
	}
}

void Tentacle::waitUpdate()
{
	activate();
}

void Tentacle::deadEffect()
{
	FOR(orbs_.size())
		EffectManager::addExplode(orbs_.at(i)->orb->getPosition());
}

void Tentacle::setOrbPosByTheirAngle()
{
	FOR(orbs_.size())
	{
		if (i > 0)
		{
			orbs_.at(i)->orb->setPos(T6Vec3(
				Default::cos(DEGREE_TO_RADIAN(orbs_.at(i)->angle)) * i * TENTACLE_ORB_DISTANCE,
				Default::sin(DEGREE_TO_RADIAN(orbs_.at(i)->angle)) * i * TENTACLE_ORB_DISTANCE,
				0.0F) + orbs_.at(0)->orb->getPosition());
		}
	}
}

void Tentacle::preparingTimeProcess()
{
	FOR(orbs_.size())
		if (orbs_.at(i)->timeCounter < Timer::getRoundTime())
			orbs_.at(i)->timeCounter = 0;
		else
			orbs_.at(i)->timeCounter -= Timer::getRoundTime();
}
