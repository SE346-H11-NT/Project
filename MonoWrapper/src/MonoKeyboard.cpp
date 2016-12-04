#include "Stdafx.h"
#include "MonoKeyboard.h"

MonoWrapper::Controller::MonoKeyboard* MonoWrapper::Controller::MonoKeyboard::m_instance = nullptr;

MonoWrapper::Controller::MonoKeyboard::MonoKeyboard()
{
	WindowsFramework::Controller::MKeyboard::initialize();
}

MonoWrapper::Controller::MonoKeyboard::~MonoKeyboard()
{

}

bool MonoWrapper::Controller::MonoKeyboard::isKeyDown(int keyCode)
{
	return WindowsFramework::Controller::MKeyboard::isKeyDown(keyCode);
}

bool MonoWrapper::Controller::MonoKeyboard::isKeyPreviouslyDown(int keyCode)
{
	return WindowsFramework::Controller::MKeyboard::isKeyPreviouslyDown(keyCode);
}

void MonoWrapper::Controller::MonoKeyboard::update()
{
	WindowsFramework::Controller::MKeyboard::update();
}

MonoWrapper::Controller::MonoKeyboard* MonoWrapper::Controller::MonoKeyboard::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new MonoWrapper::Controller::MonoKeyboard();
	}

	return m_instance;
}