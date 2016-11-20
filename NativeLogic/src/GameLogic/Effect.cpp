#include "Effect.h"



Effect::Effect(const tchar* spritePatch, int nColumns, int nRows, T6Vec3 position, DWORD delayTime /*= 0*/, int totalframe /*= 0*/)
{
	this->effectSprite_ = new T6_Sprite(spritePatch, nColumns, nRows, totalframe);
	this->delayTime_ = delayTime;
	this->position_ = position;
}


Effect::~Effect()
{
	SAFE_RELEASE(effectSprite_);
}


bool Effect::draw()
{
	if (delayTime_ > Timer::getRoundTime())
	{
		delayTime_ -= Timer::getRoundTime();
		return false;
	}

	return this->effectSprite_->render(Timer::getRoundTime(), position_, ANGLE_NO,
										SCALE_NO, TRANSLATE_NO, DrawCenter::CENTER);
}


void Effect::setFrameTime(double newTime)
{
	if (effectSprite_ != nullptr)
		effectSprite_->setFrameTime(newTime);
}

