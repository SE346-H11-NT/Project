#include "State.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

T6_Keyboard* State::controler_ = 0;
Character* State::player_ = 0;
State* State::stateList_[CharacterStatus::NUM_OF_CHARACTER_STATUS];

#pragma region Pure Virtual Base State

void State::initializeCharacterState(T6_Keyboard* keyboard, Character* player)
{
	State::controler_ = keyboard;
	State::player_ = player;

	State::stateList_[CharacterStatus::ON_GROUND] = new OnGround();
	State::stateList_[CharacterStatus::LIE_DOWN] = new LieDown();
	State::stateList_[CharacterStatus::JUMP_UP] = new JumpUp();
	State::stateList_[CharacterStatus::FALL_DOWN] = new FallDown();
	State::stateList_[CharacterStatus::DIE] = new Die();
	State::stateList_[CharacterStatus::SWIM] = new Swim();

	reset();
}


void State::releaseCharacterState()
{
	FOR_e(CharacterStatus::NUM_OF_CHARACTER_STATUS) {
		SAFE_RELEASE(State::stateList_[i]);
	}

	player_ = 0;
	controler_ = 0;
}


T6_Keyboard* State::getControler()
{
	return controler_;
}


void State::collisBullet()
{
	BulletManager::updateIfObjectIsShooted(player_, KEY_PLAYER);
}


void State::reset()
{
	player_->setStatus(stateList_[CharacterStatus::JUMP_UP]);
	player_->setVelo(SPEED_NO);
}


State* State::getState(int index)
{
	return stateList_[index];
}


T6Vec3 State::getDrawPos(T6_Texture* leg)
{
	T6Vec3 result(player_->getPosition());
	if (leg != nullptr)
		result.y += (float)leg->getFrameSize().height;
	return result;
}


void State::dead()
{
	player_->setStatus(stateList_[CharacterStatus::DIE]);
}


bool State::isWaterCollis()
{
	return true;
}


#pragma endregion

#pragma region Being on ground

// ------------------------------
// OnGround Class
// ------------------------------
void OnGround::enter()
{
	player_->switchStatusTo(CharacterStatus_Head::STRAIGHT);
	player_->switchLegStatusTo(CharacterStatus_Leg::STAND);
}


void OnGround::update()
{
	collisBullet();
	Map::affectedByGameObjects(player_, KEY_PLAYER | KEY_MOVEABLE);

	player_->updateMoveableWithCollision();

	player_->ShootObject::update();
}


void OnGround::draw(T6_Texture* head, T6_Texture* leg, DWORD fadedColor)
{
	T6Vec3 drawPos = getDrawPos(leg);
	leg->render(Timer::getRoundTime(), drawPos, 0, player_->getScale(), TRANSLATE_NO, DrawCenter::TOPCENTER, fadedColor);
	if (player_->checkIfCurrentSpriteIs(CharacterStatus_Head::DOWN45))
		drawPos.y += DISTANCE_FROM_HIP_TO_MUZZLE_DOWN45_Y;
	head->render(Timer::getRoundTime(), drawPos, 0, player_->getScale(), TRANSLATE_NO, DrawCenter::BOTTOMCENTER, fadedColor);
}


void OnGround::setMoveSprite()
{
	if (controler_->getKeyStatus(CK_UP) <= KeyStatus::KEY_PRESS)
		player_->switchStatusTo(CharacterStatus_Head::UP45);

	else if (controler_->getKeyStatus(CK_DOWN) <= KeyStatus::KEY_PRESS)
		player_->switchStatusTo(CharacterStatus_Head::DOWN45);

	else
		player_->switchStatusTo(CharacterStatus_Head::RUN_HEAD);

	player_->switchLegStatusTo(CharacterStatus_Leg::RUN_LEG);
}


void OnGround::controling()
{
	// Move left or right or stay if the keys aren't pressed.
	if (controler_->getKeyStatus(CK_RIGHT) <= KeyStatus::KEY_PRESS) {

		player_->getVelo()->x = MOVE_SPEED_RIGHT;

		setMoveSprite();
	}
	else if (controler_->getKeyStatus(CK_LEFT) <= KeyStatus::KEY_PRESS) {

		player_->getVelo()->x = MOVE_SPEED_LEFT;

		setMoveSprite();
	}
	else {
		if (player_->getVelo()->x != 0) {
			player_->getVelo()->x = 0;
			player_->switchLegStatusTo(CharacterStatus_Leg::STAND);
		}

		if (controler_->getKeyStatus(CK_UP) <= KeyStatus::KEY_PRESS)
			player_->switchStatusTo(CharacterStatus_Head::UP90);
		else
			player_->switchStatusTo(CharacterStatus_Head::STRAIGHT);
	}

	// Shoot
	if (controler_->getKeyStatus(CK_FIRE) <= KeyStatus::KEY_PRESS) {
		player_->shoot();
	}

	// Jump
	if (controler_->getKeyStatus(CK_JUMP) == KeyStatus::KEY_PRESS) {
		player_->setStatus(stateList_[CharacterStatus::JUMP_UP]);
	}

	// Lie down
	if (controler_->getKeyStatus(CK_DOWN) <= KeyStatus::KEY_PRESS) {
		if (player_->getVelo()->x == 0)
			player_->setStatus(stateList_[CharacterStatus::LIE_DOWN]);
	}

	// Dead
	if (controler_->getKeyStatus(DIK_U) <= KeyStatus::KEY_PRESS) {
		player_->setStatus(stateList_[CharacterStatus::DIE]);
	}

	// Cheatcode
	if (controler_->getKeyStatus(DIK_1) == KeyStatus::KEY_PRESS) {
		player_->changeBullet(BulletType::BASIC);
	}
	if (controler_->getKeyStatus(DIK_2) == KeyStatus::KEY_PRESS) {
		player_->changeBullet(BulletType::F);
	}
	if (controler_->getKeyStatus(DIK_3) == KeyStatus::KEY_PRESS) {
		player_->changeBullet(BulletType::L);
	}
	if (controler_->getKeyStatus(DIK_4) == KeyStatus::KEY_PRESS) {
		player_->changeBullet(BulletType::M);
	}
	if (controler_->getKeyStatus(DIK_5) == KeyStatus::KEY_PRESS) {
		player_->changeBullet(BulletType::S);
	}
	if (controler_->getKeyStatus(DIK_6) == KeyStatus::KEY_PRESS) {
		switch (Map::getCameraType())
		{
		case CAMERA_X:
			player_->fixPosition(T6Vec3(Map::getMapSize_() - 300, 100, 0) - player_->getPosition());
			break;

		case CAMERA_Y:
			player_->fixPosition(T6Vec3(100, Map::getMapSize_() - 300, 0) - player_->getPosition());
			break;

		default:
			break;
		}
	}
}


int OnGround::computeShootAngle(int& baseAngle)
{
	int directionKey = baseAngle > ANGLE_COUNTER_CLOCKWISE(90) ? CK_LEFT : CK_RIGHT;

	if (controler_->getKeyStatus(CK_UP) <= KeyStatus::KEY_PRESS)
		if (controler_->getKeyStatus(directionKey) <= KeyStatus::KEY_PRESS)
			if (directionKey == CK_RIGHT) return SHOOT_ANGLE_UP45;
			else return SHOOT_ANGLE_UP135;
		else return SHOOT_ANGLE_UP90;
	else
		if (controler_->getKeyStatus(CK_DOWN) <= KeyStatus::KEY_PRESS)
			if (controler_->getKeyStatus(directionKey) <= KeyStatus::KEY_PRESS)
				if (directionKey == CK_RIGHT) return SHOOT_ANGLE_DOWN45;
				else return SHOOT_ANGLE_DOWN135;

				return baseAngle;
}


CharacterStatus	OnGround::getIndex()
{
	return CharacterStatus::ON_GROUND;
}

Size OnGround::getBoundSize()
{
	return BOUND_SIZE_ON_GROUND;
}

#pragma endregion

#pragma region Lying down

// ------------------------------
// LieDown Class
// ------------------------------
void LieDown::enter()
{
	player_->switchStatusTo(CharacterStatus_Head::LIE);
}


void LieDown::update()
{
	collisBullet();/*

	Direction collisDirect = collisTile(Default::createRectFromBottomCenter);

	if (collisDirect == Direction::NONE) {
	player_->MoveObject::update();
	}
	else
	if (collisDirect == Direction::UP) {
	player_->setVelo(T6Vec3(player_->getVelo()->x, 0.0F, player_->getVelo()->z));
	}*/

	Map::affectedByGameObjects(player_, KEY_PLAYER | KEY_MOVEABLE);

	player_->updateDefRect(getBoundSize());

	player_->ShootObject::update();
}


void LieDown::draw(T6_Texture* head, T6_Texture* leg, DWORD fadedColor)
{
	head->render(Timer::getRoundTime(), player_->getPosition(), 0, player_->getScale(), TRANSLATE_NO, DrawCenter::BOTTOMCENTER, fadedColor);
}


void LieDown::controling()
{
	// Stand up
	if (controler_->getKeyStatus(CK_DOWN)	>= KeyStatus::KEY_RELEASE	||
		controler_->getKeyStatus(CK_LEFT)	<= KeyStatus::KEY_PRESS		||
		controler_->getKeyStatus(CK_RIGHT)	<= KeyStatus::KEY_PRESS) {
		player_->setStatus(stateList_[CharacterStatus::ON_GROUND]);
	}

	// Shoot
	if (controler_->getKeyStatus(CK_FIRE) <= KeyStatus::KEY_PRESS) {
		player_->shoot();
	}

	// Fall down
	if (controler_->getKeyStatus(CK_JUMP) <= KeyStatus::KEY_PRESS) {

		CollisEvent* standEvent = CollisEvent::isStandingOnSomething(&player_->getCollisEvent());

		if (standEvent != nullptr)
			if (dynamic_cast<Tile*>(standEvent->getTouchedObject())->getType() < TileType::TOP_UNDROP)
				player_->setStatus(stateList_[CharacterStatus::FALL_DOWN]);
	}

	// Dead
}


int LieDown::computeShootAngle(int& baseAngle)
{
	return baseAngle;
}


CharacterStatus	LieDown::getIndex()
{
	return CharacterStatus::LIE_DOWN;
}

Size LieDown::getBoundSize()
{
	return BOUND_SIZE_LIE;
}

#pragma endregion

#pragma region Jumping

// ------------------------------
// JumpUp Class
// ------------------------------
void JumpUp::enter()
{
	player_->switchStatusTo(CharacterStatus_Head::JUMP);
	player_->commandJump();
}


void JumpUp::update()
{
	collisBullet();
	Map::affectedByGameObjects(player_, KEY_PLAYER | KEY_MOVEABLE);

	player_->updateMoveableWithCollision();

	player_->ShootObject::update();
}


void JumpUp::draw(T6_Texture* head, T6_Texture* leg, DWORD fadedColor)
{
	head->render(Timer::getRoundTime(), player_->getPosition(), 0, player_->getScale(), TRANSLATE_NO, DrawCenter::BOTTOMCENTER, fadedColor);
}


void JumpUp::controling()
{
	// Move left or right or stay if the keys aren't pressed.
	if (controler_->getKeyStatus(CK_RIGHT) <= KeyStatus::KEY_PRESS) {
		player_->getVelo()->x = MOVE_SPEED_RIGHT;
	}
	else if (controler_->getKeyStatus(CK_LEFT) <= KeyStatus::KEY_PRESS) {
		player_->getVelo()->x = MOVE_SPEED_LEFT;
	}

	// Shoot
	if (controler_->getKeyStatus(CK_FIRE) <= KeyStatus::KEY_PRESS) {
		player_->shoot();
	}
}


int JumpUp::computeShootAngle(int& baseAngle)
{
	int directionKey = baseAngle > ANGLE_COUNTER_CLOCKWISE(90) ? CK_LEFT : CK_RIGHT;

	if (controler_->getKeyStatus(CK_UP) <= KeyStatus::KEY_PRESS)
		if (controler_->getKeyStatus(directionKey) <= KeyStatus::KEY_PRESS)
			if (directionKey == CK_RIGHT) return SHOOT_ANGLE_UP45;
			else return SHOOT_ANGLE_UP135;
		else return SHOOT_ANGLE_UP90;
	else
		if (controler_->getKeyStatus(CK_DOWN) <= KeyStatus::KEY_PRESS)
			if (controler_->getKeyStatus(directionKey) <= KeyStatus::KEY_PRESS)
				if (directionKey == CK_RIGHT) return SHOOT_ANGLE_DOWN45;
				else return SHOOT_ANGLE_DOWN135;

				// The difference between this state and OnGround state.
			else return SHOOT_ANGLE_DOWN90;

			return baseAngle;
}


CharacterStatus	JumpUp::getIndex()
{
	return CharacterStatus::JUMP_UP;
}

Size JumpUp::getBoundSize()
{
	return BOUND_SIZE_JUMPING;
}

#pragma endregion

#pragma region Falling from a tile

// ------------------------------
// FallDown Class
// ------------------------------
void FallDown::enter()
{
	player_->switchStatusTo(CharacterStatus_Head::FALL);
	player_->activateFallThrough();
}


void FallDown::update()
{
	collisBullet();
	Map::affectedByGameObjects(player_, KEY_PLAYER | KEY_MOVEABLE);

	player_->updateMoveableWithCollision();

	FallDown::controling();
}


void FallDown::draw(T6_Texture* head, T6_Texture* leg, DWORD fadedColor)
{
	head->render(Timer::getRoundTime(), player_->getPosition(), 0, player_->getScale(), TRANSLATE_NO, DrawCenter::BOTTOMCENTER, fadedColor);
}


void FallDown::controling()
{
	// Move left or right or stay if the keys aren't pressed.
	if (controler_->getKeyStatus(CK_RIGHT) <= KeyStatus::KEY_PRESS) {
		player_->getVelo()->x = MOVE_SPEED_RIGHT;
	}
	else if (controler_->getKeyStatus(CK_LEFT) <= KeyStatus::KEY_PRESS) {
		player_->getVelo()->x = MOVE_SPEED_LEFT;
	}

	// Shoot
	if (controler_->getKeyStatus(CK_FIRE) <= KeyStatus::KEY_PRESS) {
		player_->shoot();
	}

	// Landing

	// Dead
}


int FallDown::computeShootAngle(int& baseAngle)
{
	return baseAngle;
}


CharacterStatus	FallDown::getIndex()
{
	return CharacterStatus::FALL_DOWN;
}

Size FallDown::getBoundSize()
{
	return BOUND_SIZE_FALLING;
}

#pragma endregion

#pragma region Die state

// ------------------------------
// Die Class
// ------------------------------
void Die::enter()
{
	showTime_ = TIME_DEATH;
	player_->getVelo()->y = JUMP_SPEED_DEAD;
	player_->getVelo()->x = MOVE_SPEED_LEFT * player_->getScale().x;
	player_->switchStatusTo(CharacterStatus_Head::DEAD);
	SOUND_CODE(FreeSound::play(DIE_SOUND));
}


void Die::update()
{
	player_->ShootObject::update();

	player_->updateMoveableWithCollision();

	showTime_ -= Timer::getRoundTime();

	if (showTime_ <= 0 || (!Default::checkIfBounded(&player_->getRect(), &Camera::getViewPort()))) {
		player_->setStatus(stateList_[CharacterStatus::JUMP_UP]);
		player_->setVelo(T6Vec3(0.0F, GRAVITY * 5, player_->getVelo()->z));
		player_->reset();
	}
}


void Die::draw(T6_Texture* head, T6_Texture* leg, DWORD fadedColor)
{
	head->render(Timer::getRoundTime(), player_->getPosition(), 0, player_->getScale(), TRANSLATE_NO, DrawCenter::BOTTOMCENTER, fadedColor);
}


void Die::controling()
{

}


int Die::computeShootAngle(int& baseAngle)
{
	return baseAngle;
}


CharacterStatus	Die::getIndex()
{
	return CharacterStatus::DIE;
}

Size Die::getBoundSize()
{
	return BOUND_SIZE_DIE;
}

bool Die::isWaterCollis()
{
	return false;
}

#pragma endregion

#pragma region Swim state

// ======================================
// SWIM STATE
// ======================================
T6_Sprite* Swim::waterWave_ = nullptr;

void Swim::update()
{
	if (currentSwimState_ != SwimSubState::DIVE)
	{
		collisBullet();
		Map::affectedByGameObjects(player_, KEY_PLAYER | KEY_MOVEABLE);
		player_->ShootObject::update();
		if (currentSwimState_ != SwimSubState::CLIMB_UP)
			player_->updateMoveableWithCollision();
	}

	switch (currentSwimState_)
	{
	case FALL_IN_WATER:
		if (subStateCompleted_)
			substateSwitchTo(SwimSubState::SWIMING);

		fallInWaterTime_ += Timer::getRoundTime();
		subStateCompleted_ = (fallInWaterTime_ >= FALL_IN_WATER_TIME);
		break;

	case SWIMING:
		if (player_->checkIfReadyToClimbFromSwim()) {
			substateSwitchTo(SwimSubState::CLIMB_UP);
			player_->switchStatusTo(CharacterStatus_Head::CLIMB);
		}

		if (subStateCompleted_)
			floatPixel_ = ROUNDED_RANGE_INCREASE(floatPixel_, 1, 2);
		break;

	case CLIMB_UP:
		if (subStateCompleted_)
		{
			player_->setStatus(State::stateList_[CharacterStatus::ON_GROUND]);
			player_->fixPosition(CLIMB_DISTANCE);
		}
		break;

	case DIVE:
		break;
	default:
		substateSwitchTo(SwimSubState::FALL_IN_WATER);
		break;
	}
}


void Swim::draw(T6_Texture* head, T6_Texture* leg, DWORD fadedColor)
{
	waterWave_->render(Timer::getRoundTime(), player_->getPosition(), ANGLE_NO, SCALE_NO, TRANSLATE_NO, DrawCenter::CENTER);

	if (currentSwimState_ != SwimSubState::DIVE)
		if (currentSwimState_ != SwimSubState::FALL_IN_WATER)
			subStateCompleted_ = head->render(Timer::getRoundTime(),
			T6Vec3(player_->getPosition().x, player_->getPosition().y - floatPixel_, DEFAULT_DEPTH),
			0, player_->getScale(), TRANSLATE_NO, DrawCenter::BOTTOMCENTER, fadedColor);
}


void Swim::substateSwitchTo(SwimSubState newState)
{
	currentSwimState_ = newState;
	enter();
}


void Swim::enter()
{
	if (this->waterWave_ == nullptr)
		waterWave_ = new T6_Sprite((tstring(LINK_WATER_WAVE) + EXTENSION_PICTURE).c_str(), WATER_WAVE_COLUMNS, WATER_WAVE_ROWS, WATER_WAVE_TOTAL_FRAMES);

	subStateCompleted_ = false;

	switch (currentSwimState_)
	{
	case SwimSubState::FALL_IN_WATER:
		EffectManager::addWaterFlow(player_->getPosition());
		fallInWaterTime_ = 0;
	case SwimSubState::CLIMB_UP:
	case SwimSubState::SWIMING:
	{
		player_->switchStatusTo(CharacterStatus_Head::SWIM_STILL);
		player_->deactivate(PROPERTIES_EVATION);
		break;
	}

	case SwimSubState::DIVE:
	{
		player_->activate(PROPERTIES_EVATION);
		break;
	}

	default:
		break;
	}
}


Swim::~Swim()
{
	SAFE_RELEASE(waterWave_);
}


void Swim::setShootSprite()
{
	if (controler_->getKeyStatus(CK_UP) <= KeyStatus::KEY_PRESS){
		if (controler_->getKeyStatus(CK_LEFT) <= KeyStatus::KEY_PRESS ||
			controler_->getKeyStatus(CK_RIGHT) <= KeyStatus::KEY_PRESS)
			player_->switchStatusTo(CharacterStatus_Head::UP45);
		else
			player_->switchStatusTo(CharacterStatus_Head::UP90);
	}
	else
		player_->switchStatusTo(CharacterStatus_Head::STRAIGHT);
}


void Swim::controling()
{
	// Move left or right or stay if the keys aren't pressed.
	if (controler_->getKeyStatus(CK_RIGHT) <= KeyStatus::KEY_PRESS) {

		player_->getVelo()->x = MOVE_SPEED_RIGHT;
	}
	else if (controler_->getKeyStatus(CK_LEFT) <= KeyStatus::KEY_PRESS) {

		player_->getVelo()->x = MOVE_SPEED_LEFT;
	}
	else {
		if (player_->getVelo()->x != 0) {
			player_->getVelo()->x = 0;
		}
	}

	if (currentSwimState_ == SwimSubState::DIVE)
		if (controler_->getKeyStatus(CK_DOWN) == KeyStatus::KEY_RELEASE)
			substateSwitchTo(SwimSubState::SWIMING);

	// Shoot
	if (controler_->getKeyStatus(CK_FIRE) <= KeyStatus::KEY_PRESS) {
		setShootSprite();
		player_->shoot();
	}
	else
		player_->switchStatusTo(CharacterStatus_Head::SWIM_STILL);

	// Dive
	if (controler_->getKeyStatus(CK_DOWN) <= KeyStatus::KEY_PRESS)
		substateSwitchTo(SwimSubState::DIVE);
}


CharacterStatus	Swim::getIndex()
{
	return CharacterStatus::SWIM;
}


int Swim::computeShootAngle(int& baseAngle)
{
	int directionKey = baseAngle > ANGLE_COUNTER_CLOCKWISE(90) ? CK_LEFT : CK_RIGHT;

	if (controler_->getKeyStatus(CK_UP) <= KeyStatus::KEY_PRESS)
		if (controler_->getKeyStatus(directionKey) <= KeyStatus::KEY_PRESS)
			if (directionKey == CK_RIGHT) return SHOOT_ANGLE_UP45;
			else return SHOOT_ANGLE_UP135;
		else return SHOOT_ANGLE_UP90;

		return baseAngle;
}

Size Swim::getBoundSize()
{
	return BOUND_SIZE_SWIM;
}

#pragma endregion