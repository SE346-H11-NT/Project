#include "GameMain.h"
#include "GameUtils.h"

GameMain* GameMain::m_instance = nullptr;

NativeTexture* testTexture = nullptr;

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
	testTexture = NativeFactory::createMonoTexture("Resource\\BillAndLance");
}

void GameMain::release()
{
	NativeFactory::destroyMonoTexture(testTexture);
	SAFE_DEL(m_instance);
}

void GameMain::update(double deltaTime)
{

}

void GameMain::draw()
{
	testTexture->draw();
}
