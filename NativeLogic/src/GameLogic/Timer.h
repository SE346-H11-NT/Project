#ifndef __TIMER_H__
#define __TIMER_H__

#include <time.h>

#include "DefaultConstant.h"
#include "Camera.h"

class Timer
{
public:
	static DWORD	getRoundTime();
	static DWORD	getCameraRoundTime();
	static void		updateTimeSign();
	static void		updateRoundTime();
	static int		getRoundCode();

private:
					Timer();
					~Timer();
	static Timer&	getInstance();

private:
	static	Timer*	instance_;
			clock_t	lastTimeSign_;
			clock_t	currentTimeSign_;
			DWORD	prevRoundTime_;
			int		roundCode_;
};

#endif