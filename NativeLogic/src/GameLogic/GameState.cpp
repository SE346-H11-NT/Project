#include "GameState.h"
#include "../LibWrapper/DefaultConstant.h"

#pragma region Game State
T6_Keyboard* GameState::controler_ = nullptr;
MainMenu* MainMenu::instance_ = nullptr;

GameState* GameState::gameState_ = nullptr;

Character* GameState::player_ = nullptr;


void GameState::initialize(T6_Keyboard* controler)
{
	controler_ = controler;

	player_ = new Character(DEFAULT_STARTPOINT(0, 0));
	State::initializeCharacterState(controler_, player_);

	Map::assignPlayer(player_);

	switchState(MainMenu::get());
}

void GameState::release()
{
	SAFE_RELEASE(player_);
}


void GameState::stateUpdate()
{
	gameState_->update();
}


void GameState::switchState(GameState* newState)
{
	gameState_ = newState;
	gameState_->enter();
}


void GameState::stateDraw()
{
	gameState_->draw();
}

void GameState::update()
{

}

void GameState::draw()
{

}
#pragma endregion

#pragma region Main Menu
MainMenu::MainMenu()
{
	billAndLance_ = new T6_Texture(MAIN_MENU_RESOURCE_BILL.c_str());
	contraLogo_ = new T6_Texture(MAIN_MENU_RESOURCE_CONTRA_LOGO.c_str());
	konamiLogo_ = new T6_Texture(MAIN_MENU_RESOURCE_KONAMI_LOGO.c_str());

	selector_ = new Selector(MAIN_MENU_SELECTION_POS);

	selector_->assignSelection(MAIN_MENU_SELECTION_START);
	selector_->assignSelection(MAIN_MENU_SELECTION_CREDIT);

	enter();
}

MainMenu::~MainMenu()
{
	SAFE_RELEASE(billAndLance_);
	SAFE_RELEASE(contraLogo_);
}

void MainMenu::update()
{
	if (selectedOne_ != nullptr)
	{
		timeCounter_ += Timer::getRoundTime();

		if (timeCounter_ >= MAIN_MENU_SELECT_TIME)
		{
			if (selectedOne_ == MAIN_MENU_SELECTION_START)
			{
				switchState(StartingState::get());
			}
			else if (selectedOne_ == MAIN_MENU_SELECTION_CREDIT)
			{
				// switch to credit state
			}
		}
	}
	else
		if (Camera::getState() == CAMERA_STOP)
		{
		if (!isPlayedSound_)
		{
			SOUND_CODE(FreeSound::play(SOUND_MAINMENU_BACKGOUND, false, false));
			isPlayedSound_ = true;
		}

		if (controler_->getKeyStatus(CK_START) == KeyStatus::KEY_PRESS)
		{
			selectedOne_ = selector_->select();
		}
		}
		else
		{
			if (controler_->getKeyStatus(CK_START) == KeyStatus::KEY_PRESS)
			{
				Camera::setPosition(POSITION_ZERO);
				Camera::activateMove(POSITION_ZERO, CAMERA_STOP);
			}
		}

	if (controler_->getKeyStatus(CK_SELECT) == KeyStatus::KEY_PRESS)
	{
		selector_->toNextSelection();
	}

	cameraUpdate();
}

void MainMenu::draw()
{
	if (Camera::getState() == CameraState::CAMERA_STOP)
	{
		billAndLance_->drawImage(DRAWPOS_BILL_AND_LANCE, nullptr, SCALE_NO, TRANSLATE_NO, DrawCenter::TOPLEFT);
	}

	contraLogo_->drawImage(DRAWPOS_CONTRA_LOGO, nullptr, SCALE_NO, TRANSLATE_NO, DrawCenter::TOPLEFT);
	selector_->draw(Camera::getState() == CameraState::CAMERA_STOP);
	konamiLogo_->drawImage(DRAWPOS_KONAMI_LOGO, nullptr, SCALE_NO, TRANSLATE_NO, DrawCenter::TOPLEFT);
	TEXT_CODE(FreeText::get().drawText(MAIN_MENU_LISENCE, MAIN_MENU_LISENCE_POS, DEFAULT_FONT_COLOR, DEFAULT_FONTSIZE, DT_CENTER));
	TEXT_CODE(FreeText::get().drawText(MAIN_MENU_SELECT_ORDER, DRAWPOS_SELECT_ORDER, DEFAULT_FONT_COLOR, DEFAULT_FONTSIZE, DT_LEFT));
}

MainMenu* MainMenu::get()
{
	if (instance_ == nullptr)
		instance_ = new MainMenu();

	return instance_;
}

void MainMenu::enter()
{
	T6Vec3 cameraPos = POSITION_ZERO;
	cameraPos.x -= RESOLUTION_WIDTH;

	Camera::setPosition(cameraPos);

	cameraPos.x = -cameraPos.x;
	Camera::activateMove(cameraPos);

	isPlayedSound_ = false;
	selectedOne_ = nullptr;
	timeCounter_ = 0;
	Map::reset();
	selector_->reset();
}

void MainMenu::cameraUpdate()
{
	Camera::update(POSITION_ZERO, Timer::getCameraRoundTime());
}

#pragma endregion

#pragma region Starting

StartingState* StartingState::instance_ = nullptr;

StartingState::StartingState()
{
	isFlashOn_ = true;
	timeCounter_ = 0;
}

StartingState::~StartingState()
{

}

void StartingState::update()
{
	timeCounter_ += Timer::getRoundTime();
	if (timeCounter_ >= STARTING_FLASH_TIME)
	{
		timeCounter_ = 0;
		isFlashOn_ = !isFlashOn_;
	}

	timeCounterToNextState_ += Timer::getRoundTime();

	if (timeCounterToNextState_ >= STARTING_STATE_TIME)
	{
		switchState(PlayingState::get());
	}
}

void StartingState::draw()
{
	TEXT_CODE(FreeText::get().drawText(STARTING_STRING_1P, STARTING_STRING_POS_SCORE));
	TEXT_CODE(FreeText::get().drawText(STARTING_STRING_REST, STARTING_STRING_POS_REST));
	TEXT_CODE(FreeText::get().drawText(STARTING_STRING_HIGH_S, STARTING_STRING_POS_HIGH_S));
	TEXT_CODE(FreeText::get().drawText(tstring(STARTING_STRING_STAGE) + Default::tostr(Map::getStageIndex()), STARTING_POS_STAGE_INDEX));
	TEXT_CODE(FreeText::get().drawText(Map::getStageName(), STARTING_POS_STAGE_NAME));
	TEXT_CODE(FreeText::get().drawText(player_->getLifeRemaining(), STARTING_POS_REST));

	if (isFlashOn_)
	{
		TEXT_CODE(FreeText::get().drawText(ScoreManager::getScore(), STARTING_POS_SCORE));
		TEXT_CODE(FreeText::get().drawText(ScoreManager::getHighScore(), STARTING_POS_HIGH_S));
	}
}

void StartingState::enter()
{
	Map::reload();
	Camera::setPosition(POSITION_ZERO);
	timeCounter_ = 0;
	timeCounterToNextState_ = 0;
}

StartingState* StartingState::get()
{
	if (instance_ == nullptr)
	{
		instance_ = new StartingState();
	}

	return instance_;
}

void StartingState::cameraUpdate()
{
}

#pragma endregion

#pragma region Playing

PlayingState* PlayingState::instance_ = nullptr;

void PlayingState::update()
{
	cameraUpdate();
	if (Camera::getState() != CAMERA_AUTO)
	{
		player_->update();
		Map::update();
		BulletManager::update();

		if (player_->getLifeRemaining() < 0)
		{
			SOUND_CODE(FreeSound::stop(Map::getSoundtrackLink()));
			switchState(DeadScene::get());
		}

		if (Camera::getState() != CAMERA_STOP)
		{
			if (Map::getCameraType() == CAMERA_X)
			{
				if (Camera::getViewPort().right >= (Map::getMapSize_() - RESOLUTION_WIDTH / 2.0))
					Camera::activateMove(SPEED_X(Map::getMapSize_() - Camera::getViewPort().right));
			}
			else
			{
				if (Camera::getViewPort().top >= (Map::getMapSize_() - RESOLUTION_HEIGHT / 2.0))
					Camera::activateMove(SPEED_Y(Map::getMapSize_() - Camera::getViewPort().top));
			}
		}
	}
}

void PlayingState::draw()
{
	Map::getInstance().draw();
	player_->draw();
	BulletManager::getInstance().draw();
	EffectManager::draw();
}

void PlayingState::enter()
{
	player_->setPosition(Map::getPlayerSpawPos());
	Camera::setPosition(POSITION_ZERO);
	Camera::activateMove(POSITION_ZERO, CAMERA_NORMAL);
	SOUND_CODE(FreeSound::play(Map::getSoundtrackLink(), true, true));
}

PlayingState::PlayingState()
{

}

PlayingState::~PlayingState()
{

}

void PlayingState::cameraUpdate()
{
	if (player_->getCurrentStatus()->getIndex() != CharacterStatus::DIE)
		Camera::update(player_->getPosition(), Timer::getCameraRoundTime(), Map::getCameraType());
}

PlayingState* PlayingState::get()
{
	if (instance_ == nullptr)
	{
		instance_ = new PlayingState();
	}

	return instance_;
}


#pragma endregion

#pragma region Dead State
void DeadScene::update()
{
	timeCounter_ += Timer::getRoundTime();
	if (timeCounter_ >= STARTING_FLASH_TIME)
	{
		timeCounter_ = 0;
		isFlashOn_ = !isFlashOn_;
	}

	if (controler_->getKeyStatus(CK_START) <= KeyStatus::KEY_PRESS)
	{
		ScoreManager::reset();
		if (deadTimesRemaining_ <= 0)
		{
			deadTimesRemaining_ = DEAD_STATE_APPEAR_TIMES;
			switchState(MainMenu::get());
		}

		if (selector_->getSelectionName() == DEAD_STATE_SELECTOR_CONTINUE)
		{
			this->deadTimesRemaining_--;
			switchState(StartingState::get());
			player_->setBasicProperties();
		}
		else
		{
			deadTimesRemaining_ = DEAD_STATE_APPEAR_TIMES;
			switchState(MainMenu::get());
		}
	}

	if (controler_->getKeyStatus(CK_SELECT) == KeyStatus::KEY_PRESS)
	{
		selector_->toNextSelection();
	}
}

void DeadScene::draw()
{
	TEXT_CODE(FreeText::get().drawText(DEAD_STATE_STRING_1P, DEAD_STATE_STRING_POS_SCORE));
	TEXT_CODE(FreeText::get().drawText(DEAD_STATE_STRING_HIGH_S, DEAD_STATE_STRING_POS_HIGH_S));
	TEXT_CODE(FreeText::get().drawText(DEAD_STATE_STRING_GAMEOVER, DEAD_STATE_STRING_POS_GAMEOVER));

	if (isFlashOn_)
	{
		TEXT_CODE(FreeText::get().drawText(ScoreManager::getScore(), STARTING_POS_SCORE));
		TEXT_CODE(FreeText::get().drawText(ScoreManager::getHighScore(), STARTING_POS_HIGH_S));
	}

	if (deadTimesRemaining_ > 0)
		selector_->draw(true);
}

void DeadScene::enter()
{
	player_->setBasicProperties();
	Camera::setPosition(POSITION_ZERO);
	timeCounter_ = 0;
	selector_->reset();
}

void DeadScene::cameraUpdate()
{
}

DeadScene* DeadScene::get()
{
	if (instance_ == nullptr)
	{
		instance_ = new DeadScene();
	}

	return instance_;
}

DeadScene::DeadScene()
{
	isFlashOn_ = true;
	timeCounter_ = 0;
	deadTimesRemaining_ = DEAD_STATE_APPEAR_TIMES;
	selector_ = new Selector(DEAD_STATE_POS_SELECTOR);
	selector_->assignSelection(DEAD_STATE_SELECTOR_CONTINUE);
	selector_->assignSelection(DEAD_STATE_SELECTOR_END);
}

DeadScene::~DeadScene()
{

}

DeadScene* DeadScene::instance_ = nullptr;

#pragma endregion
