#include "Boss.h"

Boss::~Boss()
{
	FOR(subParts_.size())
		SAFE_RELEASE(subParts_.at(i));
	subParts_.clear();
}


unsigned int Boss::getScore()
{
	return SCORE_BOSS;
}


void Boss::setBasicProperties()
{
	Mobs::setBasicProperties();
	timeCounter_ = 0;
}


void Boss::assignSubPart(Mobs* newPart)
{
	subParts_.push_back(newPart);
}


void Boss::update()
{
	Mobs::update();
}


void Boss::draw()
{
	FOR(subParts_.size())
		subParts_.at(i)->draw();
}


void Boss::activateUpdate()
{

	FOR(subParts_.size())
	{
		subParts_.at(i)->updateAsBossSubpart();
		if (subParts_.at(i)->isDead())
		{
			SAFE_RELEASE(subParts_.at(i))
			subParts_.erase(subParts_.begin() + i);
		}
	}
}


void Boss::deadUpdate()
{
	FOR(subParts_.size())
	{
		subParts_.at(i)->damaged(BULLET_DAMAGE_MASSIVE);
		if (subParts_.at(i)->isDead())
		{
			SAFE_RELEASE(subParts_.at(i))
				subParts_.erase(subParts_.begin() + i);
		}
	}

	timeCounter_ += Timer::getRoundTime();

	if (timeCounter_ > BOSS_DEAD_TIME && stageClearPlayed_ == false)
	{
		SOUND_CODE(FreeSound::play(STAGE_CLEAR_SOUND));
		stageClearPlayed_ = true;
	}
}


void Boss::waitUpdate()
{
	if (Default::checkIfBounded(objectDefRect_, &Camera::getViewPort()))
		activate();
}


void Boss::deadEffect()
{
	SOUND_CODE(FreeSound::play(BOSS_DEAD_SOUND));
}


DWORD Boss::getTimeCounter()
{
	return timeCounter_;
}
