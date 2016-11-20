#include "RedSpreadBoom.h"
#include "BulletManager.h"
#include "Character.h"
#include "DestroyableObject.h"

RedSpreadBoom::RedSpreadBoom()
{
	setBasicProperties();
	bulletRS_ = BulletRS::MACHINE;
	damage_ = BULLET_DAMAGE_MASSIVE;
	ally_ = ALLY_MOBS;
}


RedSpreadBoom::~RedSpreadBoom()
{
}

void RedSpreadBoom::shoot(int angle, T6Vec3 startPoint, int ally, float scaleX)
{
	setProperties(angle, ally, scaleX);

	T6Vec3 velo = T6Vec3(RED_SPREAD_MOVE_SPEED * Default::cos(DEGREE_TO_RADIAN(angle)),
									RED_SPREAD_MOVE_SPEED * Default::sin(DEGREE_TO_RADIAN(angle)),
									0.0F);

	shoot(velo, startPoint, ally, scaleX);
}


void RedSpreadBoom::shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX)
{
	target_ = nullptr;
	setVelo(velocity);

	position_ = startPoint;

	*objectDefRect_ = Default::createRectFromCenter(position_, RED_SPREAD_BOUND_SIZE);
	timeCounter_ = 0;

	managerProcessing();
}


T6Vec3 RedSpreadBoom::generateBullet()
{
	return position_;
}

void RedSpreadBoom::update()
{
	static RED_SPREAD_BOOM_VELO;
	timeCounter_ += Timer::getRoundTime();
	MoveObject::update(Timer::getRoundTime(), Default::createRectFromCenter, RED_SPREAD_BOUND_SIZE, UPDATE_XY);

	if (timeCounter_ >= RED_SPREAD_BLOW_TIME)
	{
		bulletEffect();
		FOR(RED_SPREAD_NUM_OF_BOOM_GENERATED)
		{
			RedBoom* bullet = reinterpret_cast<RedBoom*>(manager_->getPool(BulletType::RED_BOOM)[manager_->getCounter(BulletType::RED_BOOM)]);
			bullet->shoot(generatedBoomVelo[i], position_, ally_, scale_.x);
			bullet->assignTarget(target_);
		}
	}
}

BulletType RedSpreadBoom::getType()
{
	return BulletType::RED_SPREAD_BOOM;
}

bool RedSpreadBoom::isTerminated()
{
	return (timeCounter_ >= RED_SPREAD_BLOW_TIME);
}

void RedSpreadBoom::bulletEffect()
{
	EffectManager::addExplode(position_);
}

bool RedSpreadBoom::affect(Object* obj, DWORD key)
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
			}
	}
	else
		if (ally_ == ALLY_PLAYER)
			if (Collision::checkCollision(this, obj, nullptr) >= 0)
			{
		if (!obj->isImmortal())
		{
			DestroyableObject *affectedObject = dynamic_cast<DestroyableObject *>(obj);
			if (NULL != affectedObject)
			{
				affectedObject->damaged(damage_);
			}
		}
		}

	return false;
}


void RedSpreadBoom::assignTarget(Object* target)
{
	target_ = target;
}
