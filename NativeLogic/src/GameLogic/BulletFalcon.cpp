#include "BulletFalcon.h"
#include "Character.h"

BulletFalcon::BulletFalcon(T6Vec3 position, BulletFalconType falconType)
{
	setBasicProperties();
	position_ = position;
	falconType_ = falconType;
	Object::loadObjectResource(BulletFalconType::NUM_OF_FALCON_TYPE, FALCON_LINK);
	*objectDefRect_ = Default::createRectFromBottomCenter(position, FALCON_SIZE);
	commandJump();
}


BulletFalcon::~BulletFalcon()
{
}

void BulletFalcon::update()
{
	if (updateMoveableWithCollision(FALCON_SIZE).size() > 0)
		setVelo(SPEED_NO);
}

void BulletFalcon::draw()
{
	sprites_[falconType_]->render(Timer::getRoundTime(), position_, ANGLE_NO, SCALE_NO, TRANSLATE_NO, DrawCenter::BOTTOMCENTER);
}

bool BulletFalcon::affect(Object* obj, DWORD key)
{
	if (CHECK_KEY(key, KEY_PLAYER))
		if (Collision::checkCollision(this, obj, nullptr) >= 0)
		{
		Character *player = dynamic_cast<Character *>(obj);
		if (NULL != player)
		{
			if (falconType_ == BulletFalconType::FALCON_R)
			{
				player->activateRapidShoot();
			}
			else if (falconType_ == BulletFalconType::FALCON_B)
			{
				player->activateImmortal();
			}
			else if (falconType_ == BulletFalconType::FALCON_BOOM)
			{
				player->activateBoom();
			}
			else
				player->changeBullet((BulletType)falconType_);

			return true;
		}
		}

	return false;
}

void BulletFalcon::setBasicProperties()
{
	MoveObject::setBasicProperties();
	falconType_ = BulletFalconType::FALCON_S;
}

bool BulletFalcon::isTerminated()
{
	return MoveObject::isTerminated();
}


void BulletFalcon::commandJump()
{
	MoveObject::commandJump();
	velocity_.x = MOVE_SPEED_RIGHT;
}
