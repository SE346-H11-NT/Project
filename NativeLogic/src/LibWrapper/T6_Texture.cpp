#include "T6_Texture.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif
#include <vector>

T6Matrix4			T6_Texture::cameraConvertMatrix_;
vector<T6_Texture*>	T6_Texture::loadedTexture_;

// -----------------------------------------------
// Name: T6_Texture:releaseHandler()
// Desc: Release it's properties after use (close Game).
// -----------------------------------------------
void T6_Texture::releaseHandler()
{
	FOR(loadedTexture_.size())
	{
		loadedTexture_.at(i)->releaseTexture();
		SAFE_RELEASE(loadedTexture_.at(i));
	}
	loadedTexture_.clear();
}


// -----------------------------------------------
// Name: T6_Texture:T6_Texture()
// Desc: Get the basic info, ready to load.
// -----------------------------------------------
T6_Texture::T6_Texture(const tchar* path)
{
	path_ = new tstring(path);
}


// -----------------------------------------------
// Name: T6_Texture:T6_Texture()
// Desc: Copy the info from another one.
// -----------------------------------------------
T6_Texture::T6_Texture(const T6_Texture& newTexture)
{
	this->path_		= new tstring(newTexture.path_->c_str());

	if (newTexture.isLoaded()) {
		this->texture_ = newTexture.texture_;
	}
}


// -----------------------------------------------
// Name: T6_Texture:~T6_Texture()
// Desc: Wipe out information to destroy.
// -----------------------------------------------
T6_Texture::~T6_Texture(void)
{
	SAFE_RELEASE(path_);
	texture_ = nullptr;
}

// -----------------------------------------------
// Name: T6_Texture:getName()
// Desc: Return it's path.
// -----------------------------------------------
const tchar* T6_Texture::getPath() const
{
	return this->path_->c_str();
}

// -----------------------------------------------
// Name: T6_Texture:getFrameSize()
// Desc: Return the loaded image frame size (override by T6_Sprite).
// -----------------------------------------------
Size T6_Texture::getFrameSize()
{
	if (!isLoaded())
		loadImageFromStoredInfo();

	return Size(this->getWidth(), this->getHeight());
}


// -----------------------------------------------
// Name: T6_Texture:reset()
// Desc: Set texture to it very first status.
// -----------------------------------------------
void T6_Texture::reset()
{
	
}


// -----------------------------------------------
// Name: T6_Texture:loadImageFromStoredInfo()
// Desc: Load image stored in path_.
// -----------------------------------------------
void T6_Texture::loadImageFromStoredInfo()
{
	T6_Texture* cacheTexture = tryLoadFromCache();

	if (cacheTexture != 0) {
		texture_ = cacheTexture->texture_;
		cacheTexture = 0;
	}
	else {
		texture_ = new NativeTexture(path_->c_str());
		loadedTexture_.push_back(new T6_Texture(*this));
	}
}


// -----------------------------------------------
// Name: T6_Texture:tryLoadFromCache()
// Desc: Try to find if imaged is loaded before.
// -----------------------------------------------
T6_Texture* T6_Texture::tryLoadFromCache()
{
	FOR (loadedTexture_.size())
	{
		try
		{
			if (*path_ == *(loadedTexture_.at(i)->path_))
				return loadedTexture_.at(i);
		}
		catch (exception e)
		{
			loadedTexture_.erase(loadedTexture_.begin() + i);
			i--;
		}
	}

	return 0;
}


// -----------------------------------------------
// Name: T6_Texture:isLoaded()
// Desc: Check if the texture is loaded.
// -----------------------------------------------
bool T6_Texture::isLoaded() const
{
	return (texture_ != 0);
}



// -----------------------------------------------
// Name: T6_Texture:computeCenter()
// Desc: Return the center point of the "current frame" base on draw center (the center point in the human word).
//		 Computing on machine axis(es).
// -----------------------------------------------
T6Vec3 T6_Texture::computeCenter(const DrawCenter& drawCenter)
{
		 if (drawCenter == DrawCenter::TOPLEFT		)	return T6Vec3(0.0F,								0.0F,									DEFAULT_DEPTH);
	else if (drawCenter == DrawCenter::BOTTOMLEFT	)	return T6Vec3(0.0F,								(float)getFrameSize().height,			DEFAULT_DEPTH);
	else if (drawCenter == DrawCenter::TOPCENTER	)	return T6Vec3((float)getFrameSize().width / 2.0F,	0.0F,									DEFAULT_DEPTH);
	else if (drawCenter == DrawCenter::TOPRIGHT		)	return T6Vec3((float)getFrameSize().width,			0.0F,									DEFAULT_DEPTH);
	else if (drawCenter == DrawCenter::CENTER		)	return T6Vec3((float)getFrameSize().width / 2.0F,	(float)getFrameSize().height / 2.0F,	DEFAULT_DEPTH);
	else if (drawCenter == DrawCenter::BOTTOMCENTER	)	return T6Vec3((float)getFrameSize().width / 2.0F,	(float)getFrameSize().height,			DEFAULT_DEPTH);
	else if (drawCenter == DrawCenter::BOTTOMRIGHT	)	return T6Vec3((float)getFrameSize().width,			(float)getFrameSize().height,			DEFAULT_DEPTH);
	else return GAMEPOS_TOP_LEFT;
}

// ------------------------------------------------
void T6_Texture::drawImage(T6Vec3 pos,T6Rect* srcRect, T6Vec2 scale, T6Vec2 translate,
						   const DrawCenter& drawCenter, float angle, T6Color color, bool converted)
{
	if (texture_ == 0)	{ loadImageFromStoredInfo(); }

	T6Vec3 center = computeCenter(drawCenter);

	drawImage(pos, srcRect, scale, translate, center, angle, color, converted);
}


void T6_Texture::drawImage(T6Vec3 pos /*= T6Vec3(0, 0, 0.5)*/,
	T6Rect* srcRect /*= 0*/, 
	T6Vec2 scale /*= SCALE_NO*/, 
	T6Vec2 translate /*= TRANSLATE_NO*/, 
	T6Vec3 drawCenter /*= POSITION_ZERO*/, 
	float angle /*= ANGLE_NO*/, 
	T6Color color /*= 0xFFFFFFFF*/, 
	bool converted /*= true*/)
{
	if (texture_ == 0)	{ loadImageFromStoredInfo(); }

	if (converted) {
		pos *= cameraConvertMatrix_;
	}

	angle = ANGLE_TO_RADIAN(angle);

	texture_->draw(pos.getID(), 
		srcRect != nullptr ? srcRect->getID() : -1,
		scale.getID(),
		translate.getID(),
		drawCenter.getID(),
		angle, color.getID());
}


// -----------------------------------------------
// Name: T6_Texture::render()
// Desc: Draw frame-per-frame onto screen, if it's texture, just draw it. (override by T6_Sprite)
// -----------------------------------------------
bool T6_Texture::render(double passedGameTime, T6Vec3 position,
	float angle, T6Vec2 scale, T6Vec2 translate,
	DrawCenter drawCenter, T6Color color, int from, int to,
	T6Rect* sourceRect)
{
	if (!isLoaded())
		loadImageFromStoredInfo();

	this->drawImage(position, sourceRect, scale, translate, drawCenter, angle, color);

	return true;
}


bool T6_Texture::render(double passedGameTime /*= 0.0*/, T6Vec3 position /*= T6Vec3(0, 0, 0.5)*/, float visiblePercent_width /*= 1.0f*/, float visiblePercent_height /*= 1.0f*/,
						bool isTranslateXAxis,
						T6Vec2 scale, DrawCenter drawCenter /*= DrawCenter::CENTER*/, int from /*= 0*/, int to /*= -1*/)
{
	if (!isLoaded())
		loadImageFromStoredInfo();

	T6Rect sourceRect;
	sourceRect.top = 0;
	sourceRect.left = 0;
	sourceRect.bottom = getFrameSize().height;
	sourceRect.right = getFrameSize().width;

	T6Vec3 center = computeCenter(drawCenter);

	convertVisiblePercent(visiblePercent_width, visiblePercent_height, sourceRect, position, isTranslateXAxis, scale);

	drawImage(position, &sourceRect, scale, TRANSLATE_NO, center, ANGLE_NO);

	return true;
}



// -----------------------------------------------
// Name: T6_Texture:operator=()
// Desc: Copy the information from source.
// -----------------------------------------------
T6_Texture& T6_Texture::operator=(const T6_Texture& sourceTexture)
{
	memcpy(this, &sourceTexture, sizeof(sourceTexture));
	return *this;
}


// -----------------------------------------------
// Name: T6_Texture:getCurrentFrame()
// Desc: Return the current frame, 0 if it's texture.
// -----------------------------------------------
unsigned int T6_Texture::getCurrentFrame() const
{
	return 0;
}


// -----------------------------------------------
// Name: T6_Texture:getTotalFrames()
// Desc: Return the num of frames, 1 if it's texture.
// -----------------------------------------------
unsigned int T6_Texture::getTotalFrames() const
{
	return 1;
}


// -----------------------------------------------
// Name: T6_Texture:setPositioncConvertMatrix()
// Desc: Set new matrix to convert draw position.
// -----------------------------------------------
void T6_Texture::setPositioncConvertMatrix(const T6Matrix4& newMatrix)
{
	T6_Texture::cameraConvertMatrix_ = newMatrix;
}


bool T6_Texture::isComplete()
{
	return true;
}


void T6_Texture::releaseTexture()
{
	SAFE_RELEASE(texture_);
}


T6_Texture* T6_Texture::clone() const
{
	return new T6_Texture(*this);
}


void T6_Texture::convertVisiblePercent(float width, float height, T6Rect& sourceT6Rect, T6Vec3& position, bool xAxisTranslate, T6Vec2 scale)
{
	float dWidth = sourceT6Rect.right - sourceT6Rect.left;
	float dHeight = sourceT6Rect.top - sourceT6Rect.bottom;

	if (xAxisTranslate)
		position.x += dWidth * (1 - width);
	position.y += dHeight * (1 - height);

	sourceT6Rect.bottom = sourceT6Rect.top - dHeight * height;

	if (scale.x >= 0)
		sourceT6Rect.right = sourceT6Rect.left + dWidth * width;
	else
	{
		sourceT6Rect.left = sourceT6Rect.right - dWidth * width;
	}
}

int T6_Texture::getWidth() const
{
	return texture_->getWidth();
}

int T6_Texture::getHeight() const
{
	return texture_->getHeight();
}
