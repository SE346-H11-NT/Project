#include "Stdafx.h"
#include "MonoUtils.h"
#include "MonoSound.h"

void MonoWrapper::Media::MonoSound::loadAudio(const char* path)
{
	gcroot<System::String^> rootSTR = gcnew System::String(path);
	m_ID = WindowsFramework::Media::MSound::loadSound(rootSTR);
	SAFE_DEL_ROOT(rootSTR);
}

void MonoWrapper::Media::MonoSound::play(bool isLoop)
{
	WindowsFramework::Media::MSound::playSound(m_ID, isLoop);
}

void MonoWrapper::Media::MonoSound::stop()
{
	WindowsFramework::Media::MSound::stopSound(m_ID);
}