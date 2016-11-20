#ifndef Effect_h__
#define Effect_h__

#include "GameDefaultConstant.h"
#include "Timer.h"

#include "T6_Sprite.h"

class Effect
{
public:
	Effect(const tchar* spritePatch, int nColumns, int nRows,
			T6Vec3 position, DWORD delayTime = 0, int totalframe = 0);
	~Effect();

	void setFrameTime(double newTime);
	bool draw();

private:
	T6_Sprite*	effectSprite_;
	DWORD		delayTime_;
	T6Vec3 position_;
};

#endif // Effect_h__
