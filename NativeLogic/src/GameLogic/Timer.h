#ifndef __TIMER_H__
#define __TIMER_H__

#include <time.h>

#include "DefaultConstant.h"
#include "Camera.h"
#define MONOTIME_TO_T6TIME(msec)	((clock_t)(msec))

class Timer
{
public:
	static DWORD	getRoundTime();
	static DWORD	getCameraRoundTime();
	static void		updateTimeSign(clock_t roundTime);
	static int		getRoundCode();

private:
					Timer();
					~Timer();
	static Timer&	getInstance();

private:
	static	Timer*	instance_;
			DWORD	prevRoundTime_;
			int		roundCode_;
};

#endif