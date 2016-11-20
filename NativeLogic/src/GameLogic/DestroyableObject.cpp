#include "DestroyableObject.h"
#include "BulletManager.h"
#include "Map.h"

DestroyableObject::~DestroyableObject()
{
}



bool DestroyableObject::isDead()
{
	return (heathPoints_ == 0);
}


void DestroyableObject::damaged(unsigned int damage, DWORD deadCounter)
{
	if (!isImmortal())
		if (heathPoints_ <= damage)
		{
			heathPoints_ = 0;
			dead(deadCounter);
			deadEffect();
		}
		else
		{
			heathPoints_ -= damage;
			SOUND_CODE(FreeSound::play(DAMAGE_SOUND, false, true));
		}
	else
		SOUND_CODE(FreeSound::play(DAMAGE_SOUND, false, true));
}


void DestroyableObject::dead(DWORD deadCounter)
{
	deadCounter_ = deadCounter;
}

void DestroyableObject::update()
{
	if (heathPoints_ == 0)
		if (deadCounter_ <= Timer::getRoundTime())
			deadCounter_ = 0;
		else
			deadCounter_ -= Timer::getRoundTime();
}

void DestroyableObject::setBasicProperties()
{
	Object::setBasicProperties();
	heathPoints_ = 1;
	deadCounter_ = 0;
}



void DestroyableObject::checkIfShooted()
{
	BulletManager::updateIfObjectIsShooted(this, KEY_DESTROYABLE | KEY_NO);
}


bool DestroyableObject::isTerminated()
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
