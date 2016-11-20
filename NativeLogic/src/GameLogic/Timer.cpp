#include "Timer.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

Timer* Timer::instance_ = 0;

Timer::Timer()
{
	lastTimeSign_ = clock();
	currentTimeSign_ = lastTimeSign_;
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


void Timer::updateTimeSign()
{
	clock_t*	lastTimeSign	= &Timer::getInstance().lastTimeSign_;
	clock_t*	currentTimeSign = &Timer::getInstance().currentTimeSign_;
	DWORD*		prevRoundTime	= &Timer::getInstance().prevRoundTime_;

	*lastTimeSign		= *currentTimeSign;
	*currentTimeSign	= clock();
	*prevRoundTime		= *currentTimeSign - *lastTimeSign;
	Timer::getInstance().roundCode_ = (Timer::getInstance().roundCode_ + 1) % 100;
}


void Timer::updateRoundTime()
{
	Timer::getInstance().prevRoundTime_ = (DWORD)(clock() - Timer::getInstance().currentTimeSign_);
}


int Timer::getRoundCode()
{
	return getInstance().roundCode_;
}

DWORD Timer::getCameraRoundTime()
{
	return Timer::getInstance().prevRoundTime_;
}
