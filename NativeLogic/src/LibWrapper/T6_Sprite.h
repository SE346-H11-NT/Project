//==============================
// Last change: 9/10/2014
// T6_Framework
// T6_Sprite v1.1
// This class's objects store a texture and num of columns, rows to help you
// draw the image on screen frame-per-frame for animation.
// 28/9/2014: remove Name, and change Path type to const tchar*.
// 9/10/2014: add a new properties for the time to switch frames.
//==============================
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <fstream>
#include <time.h>

#include "DefaultStructure.h"
#include "DefaultConstant.h"
#include "DefaultMethods.h"
#include "T6_Texture.h"

typedef int(*getInt)();
typedef DWORD(*getDword)();

class T6_Sprite : public T6_Texture
{
public:
	T6_Sprite():T6_Texture(){};
	T6_Sprite (const tchar* spritePatch,
				int nColumns, int nRows, int totalframe = 0, int CrF = 0);
	T6_Sprite(const T6_Sprite&	sourceSprite);
	T6_Sprite(const T6_Texture&	sourceTexture,
				const int& nColums = 1, const int& nRows = 1);
	T6_Sprite(const tchar* path, fstream& infoFile);
	virtual ~T6_Sprite(void);

	static void	synchronousProcessToNextFrame(double passedGameTime);

	bool	processToNextFrame(double passedGameTime);
	void	setFrameTime(double newTime);
	void	setFrame(const int& currentFrame = 0);
	double	getFrameTime();
	T6Rect	getSrcRect();
	int		getColumns();
	Size	getFrameSize();
	void	reset();
	bool	loadSprite();
	bool	isComplete();
	void	setAutoSwitchFrame(bool isOn);
	T6_Sprite*	 clone()			const;
	unsigned int getCurrentFrame()	const;
	unsigned int getTotalFrames()	const;


	bool render(double		passedGameTime = 0.0,
				T6Vec3	position	= T6Vec3(0,0,0.5),
				float		angle		= ANGLE_NO,
				T6Vec2	scale		= SCALE_NO,
				T6Vec2	translate	= TRANSLATE_NO,
				DrawCenter	drawCenter	= DrawCenter::CENTER,
				T6Color	color			= COLOR_HEXA_RGB(255,255,255),
				int			from		= 0,
				int			to			= -1,
				T6Rect*		sourceRect	= nullptr);


	bool render(double		passedGameTime,
				T6Vec3	position,
				float		angle,
				T6Vec2	scale,
				T6Vec2	translate,
				T6Vec3 drawCenter,
				T6Color	color = COLOR_HEXA_RGB(255, 255, 255),
				int			from = 0,
				int			to = -1,
				T6Rect*		sourceRect = nullptr);


	bool render(double		passedGameTime = 0.0,
				T6Vec3	position = T6Vec3(0, 0, 0.5),
				float		visiblePercent_width = 1.0f,
				float		visiblePercent_height = 1.0f,
				bool		isTranslateXAxis = true,
				T6Vec2	scale = SCALE_NO,
				DrawCenter	drawCenter = DrawCenter::CENTER,
				int			from = 0,
				int			to = -1);

	T6_Sprite& operator= (T6_Sprite sourceSprite);

	static void initialize(getInt getTimeCodeFunction, getDword getRoundTimeFunction);
	static void update();

private:
	double switchFrameTime_;
	double fromLastSwitch_;
	int		nColumns_,		nRows_;
	int		currentFrame_,	nFrame_;
	bool	isComplete_;
	Size	frameSize_;
	bool	autoSwitchFrame_;
	int		switchStep_;
	int		localTimeCode_;

	int		currentRenderStartPoint_;
	int		currentRenderStopPoint_;

	void caculateFrameSize();

	static vector<T6_Sprite*> synchronousSpriteList_;
	static int defaultIndex_;
	static int timeCode_;
	static DWORD timer_;
	static getInt getTimeCode_;
	static getDword getRoundTime_;
};

#endif