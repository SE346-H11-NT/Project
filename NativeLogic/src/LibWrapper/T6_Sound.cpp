#include "T6_Sound.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

// -----------------------------------------------
// Name: T6_Sound::T6_Sound()
// Desc: Get the audio Name and Path, ready to load.
// -----------------------------------------------
T6_Sound::T6_Sound(const tchar* audioPath)
{
	loadAudio(audioPath);
}



T6_Sound::~T6_Sound(void)
{
#if ENABLE_SOUND
	soundBuffer_->Stop();
#endif
}


// -----------------------------------------------
// Name: T6_Sound::loadAudio()
// Desc: Load the Audio stored in audioPath.
// -----------------------------------------------
bool T6_Sound::loadAudio(const tchar* audioPath_)
{
#if ENABLE_SOUND
#else
	return true;
#endif
}


// -----------------------------------------------
// T6_Sound::play()
// Desc: Play loaded audio, may choose loop or no.
// -----------------------------------------------
void T6_Sound::play(bool isLoop, DWORD priority)
{
#if ENABLE_SOUND
	return soundBuffer_->Play(0, priority, isLoop & DSBPLAY_LOOPING);
#endif
}


// -----------------------------------------------
// T6_Sound:stop()
// Desc: Stop the audio if it is playing.
// -----------------------------------------------
void T6_Sound::stop()
{
#if ENABLE_SOUND
	HRESULT result = soundBuffer_->Stop();
	soundBuffer_->SetCurrentPosition(0);
	return result;
#endif
}