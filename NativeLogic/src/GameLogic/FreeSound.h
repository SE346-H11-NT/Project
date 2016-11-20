#ifndef FreeSound_h__
#define FreeSound_h__

#include "T6_Sound.h"

#include <map>

typedef map<tstring, T6_Sound*> SoundMap;
typedef pair<tstring, T6_Sound*> SoundPair;

class FreeSound
{
public:
	static void initialize();
	
	static void release();

	static void play(const tchar* soundLink, bool repeat = false, bool playFromStart = true);

	static void play(tstring soundLink, bool repeat = false, bool playFromStart = true);
	
	static void stop(const tchar* soundLink);

	static void stop(tstring soundLink);

private:
	FreeSound();
	~FreeSound();
	static FreeSound* get();

private:
	static FreeSound* instance_;

	SoundMap loadedSound_;
};

#endif // FreeSound_h__
