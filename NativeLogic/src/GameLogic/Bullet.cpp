#include "Bullet.h"
#include "Mobs.h"
#include "Character.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif


void Bullet::setBasicProperties()
{
	MoveObject::setBasicProperties();
	activate(PROPERTIES_EVATION);
	activate(PROPERTIES_VISIBLE);
	gravity_ = gravityNO;
	ally_ = ALLY_PLAYER;
	sprites_ = new T6_Texture*[BulletRS::NUM_OF_BULLET_RESOURCE];
	*sprites_ = new T6_Sprite(tstring(tstring(LINK_BULLET_RS) + EXTENSION_PICTURE).c_str(), BulletRS::NUM_OF_BULLET_RESOURCE, 1);
	bulletRS_ = BulletRS::MACHINE;
	rendered_ = true;
	isLiving_ = false;
}


bool Bullet::isTerminated()
{
	if (!Default::checkIfPointInRect(position_, Camera::getViewPort()))
		return true;
	return false;
}


void Bullet::draw()
{
	if (rendered_)
		(*sprites_)->render(Timer::getRoundTime(), position_, ANGLE_NO, SCALE_NO,
		TRANSLATE_NO, DrawCenter::CENTER, COLOR_NO, bulletRS_, bulletRS_);

#if GAMEMODE == GAMEMODE_FLASH_BULLET
	rendered_ = !rendered_;
#endif
}


void Bullet::setAlly(int newAlly)
{
	ally_ = newAlly;
}


bool Bullet::isLiving()
{
	return isLiving_;
}


void Bullet::setLivingStatus(bool newLivingStatus)
{
	isLiving_ = newLivingStatus;
}


void Bullet::setProperties(int angle, int ally, float scaleX)
{
	this->shootAngle_ = angle;
	this->ally_ = ally;
	this->scaleX_ = scaleX;
}


int Bullet::getDamage()
{
	return damage_;
}


bool Bullet::affect(Object* obj, DWORD key)
{
	if (obj->isShootable())
	{
		if (CHECK_KEY(key, KEY_PLAYER))
		{
			if (ally_ == ALLY_MOBS)
				if (Collision::checkCollision(this, obj, nullptr) >= 0)
				{
				if (!obj->isImmortal())
				{
					Character *player = dynamic_cast<Character *>(obj);
					if (NULL != player)
						player->dead();
				}
				bulletEffect();
				return true;
				}
		}
		else
			if (ally_ == ALLY_PLAYER)
				if (Collision::checkCollision(this, obj, nullptr) >= 0)
				{
			DestroyableObject *affectedObject = dynamic_cast<DestroyableObject *>(obj);
			if (NULL != affectedObject)
			{
				affectedObject->damaged(damage_);

				Mobs* mobs = dynamic_cast<Mobs*>(obj);
				if (mobs != nullptr)
					if (mobs->isDead())
					{
					ScoreManager::increase(mobs->getScore());
					}
			}
			bulletEffect();
			return true;
				}
	}
	return false;
}


void Bullet::increaseVelocity(int bonusSpeed)
{
	setVelo(*getVelo() + T6Vec3(bonusSpeed * Default::cos(DEGREE_TO_RADIAN(shootAngle_)),
		bonusSpeed * Default::sin(DEGREE_TO_RADIAN(shootAngle_)),
		0.0f));
}


void Bullet::bulletEffect()
{
	EffectManager::addBulletExplode(position_);
}


void Bullet::assignManager(BulletManager& manager)
{
	manager_ = &manager;
}


void Bullet::managerProcessing()
{
	manager_->getLivingBulletList().push_back(this);

	Bullet** pool = manager_->getPool(getType());
	int* counter = &manager_->getCounter(getType());

	if (pool != nullptr)
	{
		pool[*counter] = 0;
		(*counter)--;
	}
}

int Bullet::getShootAngle()
{
	return shootAngle_;
}
