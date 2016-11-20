//==============================
// Last change: 28/9/2014
// T6_Framework
// T6_Texture v1.1
// Each object can store an image and be able to draw it on screen.
// 28/9/2014: remove Name, and change Path type to const tchar*.
//==============================
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#define CACHE_SIZE 10

#include <sstream>
#include <vector>
#include <time.h>
#include <exception>

#include "DefaultConstant.h"
#include "DefaultStructure.h"
#include "DefaultMethods.h"

#include "CSharpBridge/DLLImporter.h"

using namespace std;


class T6_Texture
{
public:
	T6_Texture(){};
	T6_Texture(const tchar* texturePath);
	T6_Texture(const T6_Texture& sourceTexture);
	virtual ~T6_Texture(void);

	static void		releaseHandler();
	static void		setPositioncConvertMatrix(const T6Matrix4& newMatrix);

	const tchar*	getPath()		const;
	bool			isLoaded()		const;
	int				getWidth()		const;
	int				getHeight()		const;

	virtual	T6_Texture*		clone()				const;
	virtual unsigned int	getCurrentFrame()	const;
	virtual unsigned int	getTotalFrames()	const;
	virtual Size			getFrameSize();
	virtual void			reset();
	virtual bool			isComplete();

	virtual void loadImageFromStoredInfo();
			void convertVisiblePercent(float width, float height, T6Rect& sourceT6Rect, T6Vec3& position, bool xAxisTranslate, T6Vec2 scale);

	void drawImage (T6Vec3				pos			= T6Vec3(0,0,0.5),
					T6Rect*				srcRect		= 0,
					T6Vec2				scale		= SCALE_NO,
					T6Vec2				translate	= TRANSLATE_NO,
					const DrawCenter&	drawCenter	= DrawCenter::CENTER,
					float				angle		= ANGLE_NO,
					T6Color			color		= 0xFFFFFFFF,
					bool				converted	= true);

	void drawImage(T6Vec3				pos,
					T6Rect*				srcRect,
					T6Vec2				scale,
					T6Vec2				translate,
					T6Vec3				drawCenter,
					float				angle = ANGLE_NO,
					T6Color			color = 0xFFFFFFFF,
					bool				converted = true);

	virtual bool render(double		passedGameTime = 0.0,
						T6Vec3		position = T6Vec3(0, 0, 0.5),
						float		angle = ANGLE_NO,
						T6Vec2		scale = SCALE_NO,
						T6Vec2		translate = TRANSLATE_NO,
						DrawCenter	drawCenter = DrawCenter::CENTER,
						T6Color		color = T6Color(255, 255, 255, 255),
						int			from = 0,
						int			to = -1,
						T6Rect*		sourceRect = nullptr);

	virtual bool render(
						double		passedGameTime = 0.0,
						T6Vec3		position = T6Vec3(0, 0, 0.5),
						float		visiblePercent_width = 1.0f,
						float		visiblePercent_height = 1.0f,
						bool		isTranslateXAxis = true,
						T6Vec2		scale = SCALE_NO,
						DrawCenter	drawCenter = DrawCenter::CENTER,
						int			from = 0,
						int			to = -1);

	T6_Texture& operator=(const T6_Texture& sourceTexture);

protected:
	T6Vec3 computeCenter(const DrawCenter& drawCenter);

private:
	void		releaseTexture();

	void		recorrectImagePositionBaseOnDrawCenter(T6Vec3& pos, const DrawCenter& drawCenter,
														const int& destWidth, const int& destHeight);

	void		transformImage(const float& angle, const T6Vec2& scale, const T6Vec2& translate,
								const T6Vec3& position, const T6Matrix4& originalStatus);

	T6_Texture* tryLoadFromCache();

private:
	static T6Matrix4			cameraConvertMatrix_;
	static vector<T6_Texture*>	loadedTexture_;

	tstring*			path_;
	NativeTexture*		texture_;
};

#endif