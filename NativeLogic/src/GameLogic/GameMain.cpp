#include "GameMain.h"
#include "GameUtils.h"

#include "LibWrapper/T6_Include.h"
#include "Timer.h"
#include "GameState.h"

GameMain* GameMain::m_instance = nullptr;

WrappedTexture* testTexture = nullptr;

GameMain::GameMain()
{

}

GameMain::~GameMain()
{

}

GameMain* GameMain::getInstance()
{
	return m_instance;
}

void GameMain::initialize()
{
	SAFE_DEL(m_instance);
	m_instance = new GameMain();
	
	T6_MergedTexture::initialize(Timer::getRoundCode, Timer::getRoundTime);
	T6_Sprite::initialize(Timer::getRoundCode, Timer::getRoundTime);
	GameState::initialize(GameMain::getInstance()->keyboard_);
}

void GameMain::release()
{
	T6_Texture::releaseHandler();
	SOUND_CODE(FreeSound::release());
	GameState::release();
	SAFE_RELEASE(GameMain::getInstance()->keyboard_);

	SAFE_DEL(m_instance);
}

void GameMain::update(double deltaTime)
{
	Timer::updateTimeSign(MONOTIME_TO_T6TIME(deltaTime));

	GameMain::getInstance()->keyboard_->update();
	GameState::stateUpdate();
	T6_Texture::setPositioncConvertMatrix(Camera::getTransform());
	T6_Text::setPositioncConvertMatrix(Camera::getTransform());
	T6_Sprite::synchronousProcessToNextFrame(deltaTime);
}

void GameMain::draw()
{
	GameState::stateDraw();
}
