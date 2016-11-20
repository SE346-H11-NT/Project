#include "FreeSound.h"


FreeSound* FreeSound::instance_ = nullptr;


FreeSound::FreeSound()
{
}


FreeSound::~FreeSound()
{
	FOR_A(loadedSound_.begin(), loadedSound_.end())
		SAFE_RELEASE(i->second);
	loadedSound_.clear();
}

void FreeSound::initialize()
{
}

void FreeSound::play(const tchar* soundLink, bool repeat /*= false*/, bool playFromStart /*= true*/)
{
#if ENABLE_SOUND
	play(tstring(soundLink), repeat, playFromStart);
#endif
}

void FreeSound::play(tstring soundLink, bool repeat /*= false*/, bool playFromStart /*= true*/)
{
#if ENABLE_SOUND
	try
	{
		if (playFromStart)
			get()->loadedSound_.at(soundLink)->stop();

		get()->loadedSound_.at(soundLink)->play(repeat);
	}
	catch (exception)
	{
		get()->loadedSound_.insert(SoundPair(soundLink, new T6_Sound(soundLink.c_str())));
		get()->loadedSound_.at(soundLink)->play(repeat);
	}
#endif
}

FreeSound* FreeSound::get()
{
	if (instance_ == nullptr)
	{
		instance_ = new FreeSound();
	}

	return instance_;
}

void FreeSound::release()
{
#if ENABLE_SOUND
	SAFE_RELEASE(instance_);
	T6_Sound::releaseSoundClass();
#endif
}

void FreeSound::stop(const tchar* soundLink)
{
#if ENABLE_SOUND
	stop(tstring(soundLink));
#endif
}


void FreeSound::stop(tstring soundLink)
{
#if ENABLE_SOUND
	try
	{
		get()->loadedSound_.at(soundLink)->stop();
	}
	catch (exception)
	{

	}
#endif
}
