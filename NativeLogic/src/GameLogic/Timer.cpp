#include "Timer.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

Timer* Timer::instance_ = 0;

Timer::Timer()
{
	prevRoundTime_ = 0;
	roundCode_ = 0;
}


Timer::~Timer()
{
	SAFE_RELEASE(instance_);
}


Timer& Timer::getInstance()
{
	if (instance_ == 0)
		instance_ = new Timer();

	return *instance_;
}


DWORD Timer::getRoundTime()
{
	if (Camera::getState() == CAMERA_AUTO)
	{
		return 0;
	}
	return Timer::getInstance().prevRoundTime_;
}

#define MAX_TIMEROUND_CODE	100
void Timer::updateTimeSign(clock_t roundTime)
{
	Timer::getInstance().prevRoundTime_  = roundTime;
	Timer::getInstance().roundCode_ = (Timer::getInstance().roundCode_ + 1) % MAX_TIMEROUND_CODE;
}

int Timer::getRoundCode()
{
	return getInstance().roundCode_;
}

DWORD Timer::getCameraRoundTime()
{
	return Timer::getInstance().prevRoundTime_;
}
