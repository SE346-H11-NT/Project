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
}


// -----------------------------------------------
// Name: T6_Sound::loadAudio()
// Desc: Load the Audio stored in audioPath.
// -----------------------------------------------
bool T6_Sound::loadAudio(const tchar* audioPath_)
{
#if ENABLE_SOUND
	m_instance.loadAudio(audioPath_);
#endif
	return true;
}


// -----------------------------------------------
// T6_Sound::play()
// Desc: Play loaded audio, may choose loop or no.
// -----------------------------------------------
void T6_Sound::play(bool isLoop, DWORD priority)
{
#if ENABLE_SOUND
	m_instance.play(isLoop);
#endif
}


// -----------------------------------------------
// T6_Sound:stop()
// Desc: Stop the audio if it is playing.
// -----------------------------------------------
void T6_Sound::stop()
{
#if ENABLE_SOUND
	m_instance.stop();
#endif
}