#include "T6_ColormapTexture.h"


int T6_ColormapTexture::currentColor_ = 0;

DWORD T6_ColormapTexture::color[] = { 0xFFFF8C7C, 0xFFE44434, 0xFFB81C0C };

T6_ColormapTexture::T6_ColormapTexture(const tchar* spritePatch) :
					T6_MergedTexture(spritePatch, 2, 1)
{
}


T6_ColormapTexture::~T6_ColormapTexture()
{
}

void T6_ColormapTexture::draw(index_t index,
							  T6Vec3 position,
							  DrawCenter drawCenter /*= DrawCenter::TOPLEFT*/,
							  T6Vec2 scale /*= SCALE_NO*/,
							  T6Vec2 translate /*= TRANSLATE_NO*/,
							  float angle /*= ANGLE_NO*/,
							  T6Color fadedColor /*= 0xFFFFFFFF*/)
{
	T6_MergedTexture::draw(0, position, drawCenter, scale, translate, angle);
	T6_MergedTexture::draw(1, position, drawCenter, scale, translate, angle, fadedColor);
}

bool T6_ColormapTexture::render(double passedGameTime /*= 0.0*/,
	T6Vec3 position /*= T6Vec3(0, 0, 0.5)*/,
	float angle /*= ANGLE_NO*/,
	T6Vec2 scale /*= SCALE_NO*/,
	T6Vec2 translate /*= TRANSLATE_NO*/,
	DrawCenter drawCenter /*= DrawCenter::CENTER*/,
	T6Color fcolor /*= COLOR_HEXA_RGB(255, 255, 255)*/,
	int from /*= 0*/,
	int to /*= -1*/)
{
	if (!isLoaded())
		loadMergedTexture();
	draw(0, position, drawCenter, scale, translate, angle, color[currentColor_]);
	processToNextColor(passedGameTime);
	return true;
}


void T6_ColormapTexture::processToNextColor(double passedGameTime)
{
	if (this->fromLastSwitch_ < SWITCH_COLOR_TIME)
		fromLastSwitch_ += passedGameTime;
	else {
		currentColor_ = (currentColor_ + 1) % 3;
		fromLastSwitch_ = 0;
	}
}