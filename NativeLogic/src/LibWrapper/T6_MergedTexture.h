#ifndef __MERGED_TEXTURE_H__
#define __MERGED_TEXTURE_H__

#include "T6_Texture.h"

typedef int(*getInt)();
typedef DWORD(*getDword)();

#define DEFAULT_INDEX	-1

class T6_MergedTexture : public T6_Texture
{
public:
	T6_MergedTexture(const tchar* spritePatch, int nColumns, int nRows);
	T6_MergedTexture(const T6_MergedTexture& sourceMTexture);
	virtual ~T6_MergedTexture();

	virtual void draw  (index_t index,
				T6Vec3 position,
				DrawCenter drawCenter	= DrawCenter::TOPLEFT,
				T6Vec2 scale		= SCALE_NO,
				T6Vec2 translate	= TRANSLATE_NO,
				float angle				= ANGLE_NO,
				T6Color fadedColor		= 0xFFFFFFFF);

	virtual void draw(index_t index,
					  T6Vec3 position,
					  float percentOfVisible_width,
					  float percentOfVisible_height,
					  bool	isTranslateXAxis = true,
					  DrawCenter drawCenter	= DrawCenter::TOPLEFT,
					  T6Vec2 scale		= SCALE_NO,
					  T6Vec2 translate	= TRANSLATE_NO,
					  float angle			= ANGLE_NO,
					  T6Color fadedColor	= 0xFFFFFFFF);

	Size getFrameSize();

	void loadMergedTexture();
	T6_MergedTexture* clone() const;
	static void initialize(getInt getTimeCodeFunction, getDword getRoundTimeFunction);
	static void update();

private:
	int rows_;
	int columns_;
	Size frameSize_;
	static int defaultIndex_;
	static int timeCode_;
	static DWORD timer_;
	static getInt getTimeCode_;
	static getDword getRoundTime_;

	T6Rect** imageRectCache_;
};

#endif