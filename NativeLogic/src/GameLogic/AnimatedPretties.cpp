#include "AnimatedPretties.h"
#include "DefaultStructure.h"
#include "T6_Sprite.h"

AnimatedPretties::AnimatedPretties(tstring path, index_t index, size_t rows, T6Vec3 position, int frameNum)
	: Pretties(path, index * frameNum, rows, frameNum, position, RESOURCE_MS)
{
	frameNum_ = frameNum;
	((T6_Sprite*)(*sprites_))->setAutoSwitchFrame(false);
}


AnimatedPretties::~AnimatedPretties()
{
}


void AnimatedPretties::draw()
{
	(*sprites_)->render(0, position_,
						ANGLE_NO, SCALE_NO, TRANSLATE_NO, DrawCenter::BOTTOMLEFT,
						COLOR_NO, index_, index_ + frameNum_);
}


void AnimatedPretties::update()
{

}