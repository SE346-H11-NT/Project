#include "Character.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif


Character::Character(T6Vec3 position)
{
	setBasicProperties();
	this->position_ = position;

	Object::loadObjectResource(CharacterStatus_Leg::NUM_OF_C_LEG_STATUS, LINK_CHARACTER_LEG);

	spriteCharLeg_ = sprites_;
	sprites_ = 0;

	Object::loadObjectResource(CharacterStatus_Head::NUM_OF_C_HEAD_STATUS, LINK_CHARACTER_HEAD);


	*this->objectDefRect_ = Default::createRectFromBottomCenter(position_, sprites_[status_]->getFrameSize());
	ScoreManager::initialize(this);
}


Character::~Character()
{
	State::releaseCharacterState();

	SAFE_RELEASE(spriteCharLeg_);
}


void Character::update()
{
	currentState_->controling();
	currentState_->update();

	if (isImmortal())
	{
		immortalTime_ += Timer::getRoundTime();
		if ((immortalTime_ >= CHARACTER_IMMORTAL_TIME && !immortalBulletActivate_) ||
			(immortalTime_ >= CHARACTER_BULLET_IMMORTAL_TIME && immortalBulletActivate_))
		{
			deactivate(PROPERTIES_IMMORTAL);
		}
	}
}


void Character::draw()
{
	static DWORD immortalColors[] = { 0xFFFF0000, 0xFF0000FF };
	static DWORD respawColors[] = { COLOR_NO, 0x00000000 };
	static int colorIndex = 0;
	static DWORD timer = 0;
	static T6_Texture lifeIcon = T6_Texture(CHARACTER_EXTRA_LIFE_RESOURCE_LINK.c_str());

	DWORD color = COLOR_NO;

	if (isImmortal())
	{
		timer += Timer::getRoundTime();
		if (timer >= DEFAULT_FRAME_TIME)
		{
			// 2 is the number of faded colors which is declared above
			colorIndex = (colorIndex + 1) % 2;
			timer = 0;
		}

		if (immortalBulletActivate_)
		{
			color = immortalColors[colorIndex];\
		}
		else
		{
			color = respawColors[colorIndex];
		}
	}

	currentState_->draw(sprites_[status_], spriteCharLeg_[status_leg_], color);

	FOR(getLifeRemaining())
	{
		if (i >= CHARACTER_NUM_OF_MAX_LIFE_ICON)
		{
			break;
		}

		// The objects which is not converted as a thing in game world must be compute the draw position
		// by the machine coordinates
		T6Vec3 lifePos = WDPOS_TOP_LEFT;
		lifePos.y += CHARACTER_LIFE_ICON_Y_FIX;
		lifePos.x += i * (lifeIcon.getFrameSize().width + CHARACTER_LIFE_ICON_X_FIX) + CHARACTER_LIFE_ICON_DISTANCE_TO_LEFT;
		lifeIcon.drawImage(lifePos, nullptr, SCALE_NO, TRANSLATE_NO, DrawCenter::TOPLEFT, ANGLE_NO, COLOR_NO, false);
	}
}


void Character::setBasicProperties()
{
	static RELOAD_TIME;
	ShootObject::setBasicProperties();
	MoveObject::setBasicProperties();
	currentBullet_ = BulletType::BASIC;
	this->lastShootTime_ = reload[(currentBullet_)];
	this->status_ = CharacterStatus_Head::RUN_HEAD;
	this->status_leg_ = CharacterStatus_Leg::RUN_LEG;
	this->velocity_ = SPEED_NO;

	currentTouchableStatus_ = &Object::propertiesNo;
	this->life_ = DEFAULT_LIFE;
}


void Character::setStatus(State* newState)
{
	if (currentState_ != newState) {
		currentState_ = newState;
		currentState_->enter();
	}
}


void Character::switchLegStatusTo(unsigned int newStatus)
{
	if (status_leg_ != newStatus) {
		spriteCharLeg_[status_leg_]->reset();
		status_leg_ = newStatus;
	}
}


int Character::reset()
{
	position_ = Map::computeRespawPos();
	velocity_ = SPEED_NO;
	immortalBulletActivate_ = false;
	immortalTime_ = 0;
	Object::activate(PROPERTIES_IMMORTAL);
	changeBullet(BulletType::BASIC);
	State::reset();
	life_--;
	deactivateFallThrough();

	return life_;
}


Bullet* Character::shoot()
{
	if (status_ == CharacterStatus_Head::RUN_HEAD)
		switchStatusTo(CharacterStatus_Head::STRAIGHT);

	static RELOAD_TIME;

	if (lastShootTime_ >= reload[(currentBullet_)]) {
		lastShootTime_ = Timer::getRoundTime();

		Bullet* shootedOne = BulletManager::getInstance().shoot(currentBullet_, ALLY_PLAYER, computeShootPoint(), computeShootAngle(), scale_.x);
		if (bonusBulletSpeed_ != 0 && shootedOne != nullptr)
		{
			shootedOne->increaseVelocity(bonusBulletSpeed_);
		}

		return shootedOne;
	}

	return 0;
}


int	Character::computeShootAngle()
{
	int angle = (int)ANGLE_BASIC_SX(scale_.x);
	return currentState_->computeShootAngle(angle);
}


T6Vec3 Character::computeShootPoint()
{
	T6Vec3 startpoint(position_.x,
		position_.y,
		DEFAULT_DEPTH);

	if (currentState_->getIndex() == CharacterStatus::ON_GROUND ||
		currentState_->getIndex() == CharacterStatus::FALL_DOWN)
		startpoint.y += (float)spriteCharLeg_[status_leg_]->getFrameSize().height;

	switch (this->status_)
	{
	case CharacterStatus_Head::UP90:
		startpoint.x += (float)(scale_.x * 4);
		startpoint.y += (float)(sprites_[status_]->getFrameSize().height);
		break;

	case CharacterStatus_Head::UP45:
		startpoint.x += (float)(scale_.x * (sprites_[status_]->getFrameSize().width / 2));
		startpoint.y += (float)(sprites_[status_]->getFrameSize().height);
		break;

	case CharacterStatus_Head::STRAIGHT:
		startpoint.x += (float)(scale_.x * (sprites_[status_]->getFrameSize().width / 2));
		startpoint.y += (float)(DISTANCE_FROM_HIP_TO_MUZZLE_STRAIGHT_Y);
		break;

	case CharacterStatus_Head::DOWN45:
		startpoint.x += (float)(scale_.x * (sprites_[status_]->getFrameSize().width / 2));
		startpoint.y += (float)(DISTANCE_FROM_HIP_TO_MUZZLE_DOWN45_Y);
		break;

	case CharacterStatus_Head::FALL:
		startpoint.x += (float)(scale_.x * (sprites_[status_]->getFrameSize().width / 2));
		startpoint.y += (float)(DISTANCE_FROM_HIP_TO_MUZZLE_FALL_Y);
		break;

	case CharacterStatus_Head::JUMP:
		startpoint.y += (float)(spriteCharLeg_[status_leg_]->getFrameSize().height / 2);
		break;

	case CharacterStatus_Head::LIE:
		startpoint.x += (float)(scale_.x * (sprites_[status_]->getFrameSize().width / 2));
		startpoint.y += (float)(DISTANCE_FROM_HIP_TO_MUZZLE_LIE_Y);
		break;

	default:
		break;
	}

	return startpoint;
}


int Character::getCurrentLegSpriteFrame()
{
	return spriteCharLeg_[status_leg_]->getCurrentFrame();
}


void Character::setLegFrame(int frame)
{
	((T6_Sprite*)spriteCharLeg_[status_leg_])->setFrame(frame);
}


State* Character::getCurrentStatus()
{
	return currentState_;
}


vector<CollisEvent*> Character::updateMoveableWithCollision()
{
	MoveObject::updateMoveableWithCollision(currentState_->getBoundSize(), currentState_->isWaterCollis());
	if (position_.y < Camera::getViewPort().bottom)
	{
		if (currentState_->getIndex() != DIE)
			dead();
	}

	CollisEvent* standingSignCollisEvent = CollisEvent::isStandingOnSomething(&currentCollisEvents_, &getRect(),
		fallThrough_ ?
		&ignoredCollisObject_ : nullptr);

	if (standingSignCollisEvent == nullptr){ // Not standing on anything
		if (!IS_UPDATING_Y(this->getCurrentStatus()->getIndex())) // If current status is not allow to Update Y-axis
			this->setStatus(State::getState(CharacterStatus::FALL_DOWN));
	}
	else // If standing on something
		if (this->getCurrentStatus()->getIndex() != CharacterStatus::DIE){ // If not dying
		this->setStatus(State::getState((dynamic_cast<Tile*>(standingSignCollisEvent->getTouchedObject())->getTouchedStatus())));
		/*this->setVelo(T6Vec3(this->getVelo()->x, TRUE_SPEED(GRAVITY, Timer::getRoundTime()), this->getVelo()->z));*/
		this->deactivateFallThrough();
		}
		else { // If dying
			this->switchStatusTo(CharacterStatus_Head::DIE_ALREADY);
			this->setVelo(T6Vec3(0.0F, TRUE_SPEED(GRAVITY, Timer::getRoundTime()), this->getVelo()->z));
		}

		return currentCollisEvents_;
}


bool Character::checkIfReadyToClimbFromSwim()
{
	// BUGGED
	FOR(currentCollisEvents_.size())
		if ((dynamic_cast<Tile*>(currentCollisEvents_[i]->getTouchedObject()))->getType() >= TileType::FOUR_FACE)
			if ((currentCollisEvents_[i]->getDirection() == Direction::RIGHT && this->getVelo()->x > 0) ||
				(currentCollisEvents_[i]->getDirection() == Direction::LEFT && this->getVelo()->x < 0))
				return true;

	return false;
}


void Character::dead()
{
	State::dead();
	bonusBulletSpeed_ = 0;
	immortalTime_ = RESPAW_IMMORTAL_TIME;
	changeBullet(BulletType::BASIC);
}

bool Character::affect(Object* obj, DWORD key)
{
	return false;
}

void Character::activateRapidShoot()
{
	bonusBulletSpeed_ = RAPID_SHOOT_BONUS_SPEED;
}

void Character::activateImmortal()
{
	Object::activate(PROPERTIES_IMMORTAL);
	immortalBulletActivate_ = true;
	immortalTime_ = 0;
}

void Character::activateBoom()
{

}

bool Character::isTerminated()
{
	return false;
}


void Character::updateDefRect(Size boundRange)
{
	*objectDefRect_ = Default::createRectFromBottomCenter(position_, boundRange);
}

int Character::getLifeRemaining()
{
	return life_;
}

void Character::bonusLife()
{
	life_ += 1;
	// sound
}
