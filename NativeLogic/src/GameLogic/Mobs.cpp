#include "Mobs.h"
#include "Character.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif


void Mobs::setBasicProperties()
{
	DestroyableObject::setBasicProperties();
	this->mobState_ = MobState::MOBS_STATE_WAIT;
}


void Mobs::suspend()
{
	this->mobState_ = MOBS_STATE_WAIT;
}

void Mobs::activate()
{
	this->mobState_ = MOBS_STATE_ACTIVATE;
}


void Mobs::update()
{
	DestroyableObject::update();

	switch (mobState_)
	{
	case MOBS_STATE_WAIT:
		waitUpdate();
		break;

	case MOBS_STATE_ACTIVATE:
		if (isDead())	deadUpdate();
		else			activateUpdate();
		break;

	default:
		break;
	}
}


void Mobs::compulsoryDead()
{
	Mobs::dead(0);
}



bool Mobs::affect(Object* obj, DWORD key)
{
	if (CHECK_KEY(key, KEY_PLAYER))
		if (this->isTouchable() && !isDead() && isActivated() && !obj->isImmortal())
			if (Collision::checkCollision(obj, this, nullptr) >= 0)
			{
				Character *player = dynamic_cast<Character *>(obj);
				if (NULL != player)
				{
					player->dead();
				}
			}

	return false;
}


bool Mobs::isActivated()
{
	return (mobState_ == MobState::MOBS_STATE_ACTIVATE);
}


void Mobs::updateAsBossSubpart()
{
	activateUpdate();
}
