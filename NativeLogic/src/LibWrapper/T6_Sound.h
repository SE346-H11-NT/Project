//==============================
// Last change: 29/9/2014
// T6_Framework
// T6_Sound v1.v
// Store the class help you to load and play a wav audio.
// 29/9/2014: Add the cache system, allow reuse the loaded audio data.
//==============================
#ifndef __SOUND_H__
#define __SOUND_H__

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dxguid.lib")

#include <dsound.h>
#include <vector>
#include <memory>

#include "DefaultConstant.h"
#include "DefaultStructure.h"

#include "CSharpBridge/DLLImporter.h"


// -----------------------------------------------
// Name: class T6_Sound
// Desc: used to load/ store/ play an audio with wav extension.
// -----------------------------------------------
class T6_Sound
{
public:
	T6_Sound(const tchar* audioPath);
	~T6_Sound(void);

	void play(bool isLoop = false, DWORD priority = 0);
	void stop();


private:
	bool loadAudio(const tchar* audioPath);

private:
	WrappedSound	m_instance;
};

#endif