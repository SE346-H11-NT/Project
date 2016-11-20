#ifndef __COLOR_MAP_TEXTURE_H__
#define __COLOR_MAP_TEXTURE_H__

#include "T6_MergedTexture.h"

#define NUM_OF_COLOR_MAP_TEXTURE_COLOR	3
#define SWITCH_COLOR_TIME	100

class T6_ColormapTexture : public T6_MergedTexture
{
public:
	T6_ColormapTexture(const tchar* spritePatch);
	virtual ~T6_ColormapTexture();

	void draw(index_t index,
				T6Vec3 position,
				DrawCenter drawCenter = DrawCenter::TOPLEFT,
				T6Vec2 scale = SCALE_NO,
				T6Vec2 translate = TRANSLATE_NO,
				float angle = ANGLE_NO,
				T6Color fadedColor = 0xFFFFFFFF);

	void processToNextColor(double passedGameTime);

	virtual bool render(double passedGameTime = 0.0,
						T6Vec3 position = T6Vec3(0, 0, 0.5),
						float angle = ANGLE_NO,
						T6Vec2 scale = SCALE_NO,
						T6Vec2 translate = TRANSLATE_NO,
						DrawCenter drawCenter = DrawCenter::CENTER,
						T6Color color = COLOR_HEXA_RGB(255, 255, 255), int from = 0, int to = -1);

private:
	static DWORD color[];
	static int currentColor_;

	double switchColorTime_;
	double fromLastSwitch_;
};

#endif