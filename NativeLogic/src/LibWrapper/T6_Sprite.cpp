#include "T6_Sprite.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif


vector<T6_Sprite*> T6_Sprite::synchronousSpriteList_;

// -----------------------------------------------
// Name: T6_Sprite:T6_Sprite()
// Desc: Store new info to ready to load and use.
// -----------------------------------------------
T6_Sprite::T6_Sprite(const tchar* spritePath,
	int nColumns, int nRows, int nFrame,
	int currentFrame) : T6_Texture(spritePath)
{
	this->isComplete_ = true;
	this->nColumns_ = nColumns;
	this->nRows_ = nRows;
	this->currentFrame_ = currentFrame;
	this->fromLastSwitch_ = 0;
	this->autoSwitchFrame_ = true;
	this->switchFrameTime_ = DEFAULT_FRAME_TIME;

	if (nFrame > 0)
		this->nFrame_ = nFrame;
	else
		this->nFrame_ = nRows_ * nColumns_;
}


// -----------------------------------------------
// Name: T6_Sprite:T6_Sprite()
// Desc: Copy information from source sprite.
// -----------------------------------------------
T6_Sprite::T6_Sprite(const T6_Sprite& sourceSprite) : T6_Texture(sourceSprite)
{
	this->isComplete_ = true;
	this->currentFrame_ = 0;
	this->nColumns_ = sourceSprite.nColumns_;
	this->nRows_ = sourceSprite.nRows_;
	this->nFrame_ = sourceSprite.nFrame_;
	this->fromLastSwitch_ = 0;
	this->autoSwitchFrame_ = sourceSprite.autoSwitchFrame_;
	this->switchFrameTime_ = sourceSprite.switchFrameTime_;

	if (this->isLoaded()) {
		this->frameSize_ = sourceSprite.frameSize_;
	}
}


// -----------------------------------------------
// Name: T6_Sprite:T6_Sprite()
// Desc: Create a sprite from a texture.
// -----------------------------------------------
T6_Sprite::T6_Sprite(const T6_Texture& sourceTexture,
	const int& nColumns, const int& nRows) : T6_Texture(sourceTexture)
{
	this->isComplete_ = true;
	this->nColumns_ = nColumns;
	this->nRows_ = nRows;
	this->currentFrame_ = 0;
	this->fromLastSwitch_ = 0;
	this->autoSwitchFrame_ = true;
	this->switchFrameTime_ = DEFAULT_FRAME_TIME;

	if (this->isLoaded())
		caculateFrameSize();
}


// -----------------------------------------------
// Name: T6_Sprite:T6_Sprite()
// Desc: Create a sprite from read info.
// -----------------------------------------------
T6_Sprite::T6_Sprite(const tchar* path, fstream& infoFile)
{
	int columns;
	int rows;
	int totalFrames;

	infoFile >> columns;
	infoFile >> rows;
	infoFile >> totalFrames;

	this->T6_Sprite::T6_Sprite(path, columns, rows, totalFrames);
	this->switchFrameTime_ = DEFAULT_FRAME_TIME;
	this->autoSwitchFrame_ = true;
}


// -----------------------------------------------
// Name: T6_Sprite:~T6_Sprite()
// Desc: 
// -----------------------------------------------
T6_Sprite::~T6_Sprite(void)
{
}


// -----------------------------------------------
// Name: T6_Sprite:caculateFrameSize()
// Desc: Base on num of Columns and Rows, this function will calculate frame size base on image resolution.
// -----------------------------------------------
void T6_Sprite::caculateFrameSize()
{
	this->frameSize_.width = (int)((float)getWidth() / (float)this->nColumns_);
	this->frameSize_.height = (int)((float)getHeight() / (float)this->nRows_);
}


// -----------------------------------------------
// Name: T6_Sprite:reset()
// Desc: Override from T6_Texture, reset it to very first status.
// -----------------------------------------------
void T6_Sprite::reset()
{
	this->setFrame(0);
	this->isComplete_ = false;
	this->fromLastSwitch_ = 0;
}


// -----------------------------------------------
// Name: T6_Sprite:loadSprite()
// Desc: Load image and calculate frame size base on stored info.
// -----------------------------------------------
bool T6_Sprite::loadSprite()
{
	T6_Texture::loadImageFromStoredInfo();

	if (!this->isLoaded()) {
		WARNING_BOX("Cannot loat sprite");
		return false;
	}

	caculateFrameSize();
	return true;
}


// -----------------------------------------------
// Name: T6_Sprite:processToNextFrame()
// Desc: Check and process if it's time to jump to next frame.
// -----------------------------------------------
bool T6_Sprite::processToNextFrame(double passedGameTime)
{
	if (this->fromLastSwitch_ < switchFrameTime_)
		fromLastSwitch_ += passedGameTime;
	else {
		currentFrame_ += switchStep_;
		fromLastSwitch_ = 1;
	}

	if (currentFrame_ == currentRenderStopPoint_) {
		currentFrame_ = currentRenderStartPoint_;
		fromLastSwitch_ = 0;
		this->isComplete_ = true;
		return true;
	}
	else {
		this->isComplete_ = false;
		return false;
	}
}


// -----------------------------------------------
// Name: T6_Sprite:render()
// Desc: Draw frame-per-frame onto screen.
// -----------------------------------------------
bool T6_Sprite::render(double passedGameTime, T6Vec3 position,
	float angle, T6Vec2 scale, T6Vec2 translate,
	DrawCenter drawCenter, T6Color color, int from, int to, T6Rect* sourceRect)
{
	if (!isLoaded())	{ loadSprite(); }

	T6_Sprite::update();

	if (passedGameTime == 0)
	{
		from += defaultIndex_;
		to += defaultIndex_;
	}

	T6Vec3 center = computeCenter(drawCenter);

	return render(passedGameTime, position, angle, scale, translate, center, color, from, to, sourceRect);
}



bool T6_Sprite::render(double passedGameTime /*= 0.0*/, 
						T6Vec3 position /*= T6Vec3(0, 0, 0.5)*/, 
						float visiblePercent_width,
						float visiblePercent_height,
						bool isTranslateXAxis,
						T6Vec2 scale,
						DrawCenter drawCenter /*= DrawCenter::CENTER*/, 
						int from /*= 0*/,
						int to /*= -1*/)
{
	if (!isLoaded())	{ loadSprite(); }

	T6_Sprite::update();

	if (passedGameTime == 0)
	{
		from += defaultIndex_;
		to += defaultIndex_;
	}

	T6Rect* sourceRect = new T6Rect(getSrcRect());

	T6Vec3 center = computeCenter(drawCenter);

	convertVisiblePercent(visiblePercent_width, visiblePercent_height, *sourceRect, position, isTranslateXAxis, scale);

	bool result = render(passedGameTime, position, ANGLE_NO, scale, TRANSLATE_NO, center, COLOR_NO, from, to, sourceRect);
	SAFE_RELEASE(sourceRect);

	return result;
}


bool T6_Sprite::render(double passedGameTime /*= 0.0*/, T6Vec3 position /*= T6Vec3(0, 0, 0.5)*/, float angle /*= ANGLE_NO*/, T6Vec2 scale /*= SCALE_NO*/, T6Vec2 translate /*= TRANSLATE_NO*/, T6Vec3 drawCenter /*= POSITION_ZERO*/, T6Color color /*= COLOR_HEXA_RGB(255, 255, 255)*/, int from /*= 0*/, int to /*= -1*/, T6Rect* sourceRect /*= nullptr*/)
{
	if (to < 0)
		to = this->nFrame_;

	if (from < 0)
		from = this->nFrame_ - 1;

	if (to >= from)
	{
		switchStep_ = 1;
	}
	else
	{
		switchStep_ = -1;
		to--;
	}

	if (fromLastSwitch_ == 0)
		currentFrame_ = from;

	currentRenderStartPoint_ = from;
	currentRenderStopPoint_ = to;

	if (!isLoaded())
		loadSprite();

	if (sourceRect == nullptr)
	{
		T6Rect rect;
		rect = getSrcRect();
		this->drawImage(position, &rect, scale, translate, drawCenter, angle, color);
	}
	else
		this->drawImage(position, sourceRect, scale, translate, drawCenter, angle, color);

	if (autoSwitchFrame_)
		return processToNextFrame(passedGameTime);

	return false;
}



// -----------------------------------------------
// Name: T6_Sprite:setFrame()
// Desc: Jump the current frame to this point.
// -----------------------------------------------
void T6_Sprite::setFrame(const int& currentFrame)
{
	currentFrame_ = currentFrame;
}


// -----------------------------------------------
// Name: T6_Sprite:getSrcRect()
// Desc: Calculate and return the Rectangle define current draw range on texture.
// -----------------------------------------------
T6Rect T6_Sprite::getSrcRect()
{
	T6Rect rect;
	rect.left = (UINT)frameSize_.width  * (currentFrame_ - (int)(currentFrame_ / nColumns_) * nColumns_);
	rect.top = (UINT)frameSize_.height * (int)(currentFrame_ / nColumns_);
	rect.right = rect.left + (UINT)frameSize_.width;
	rect.bottom = rect.top + (UINT)frameSize_.height;
	return rect;
}


// -----------------------------------------------
// Name: T6_Sprite:getColumns()
// Desc: Return it's num of columns.
// -----------------------------------------------
int T6_Sprite::getColumns()
{
	return nColumns_;
}



// -----------------------------------------------
// Name: T6_Sprite:getFrameSize()
// Desc: Override from T6_Texture's method, return the size of per frame.
// -----------------------------------------------
Size T6_Sprite::getFrameSize()
{
	if (!isLoaded())
		loadSprite();

	if (frameSize_.x == 0 || frameSize_.y == 0)
	{
		caculateFrameSize();
	}

	return frameSize_;
}



// -----------------------------------------------
// Name: T6_Sprite:operator=()
// Desc: Copy information from source Sprite.
// -----------------------------------------------
T6_Sprite& T6_Sprite::operator=(T6_Sprite sourceSprite)
{
	memcpy(this, &sourceSprite, sizeof(sourceSprite));
	return *this;
}


// -----------------------------------------------
// Name: T6_Sprite:getCurrentFrame()
// Desc: Override from Texture, return the current frame.
// -----------------------------------------------
unsigned int T6_Sprite::getCurrentFrame() const
{
	return currentFrame_;
}


// -----------------------------------------------
// Name: T6_Sprite:getTotalFrames()
// Desc: Override from Texture, return the num of frames.
// -----------------------------------------------
unsigned int T6_Sprite::getTotalFrames() const
{
	return nFrame_;
}


bool T6_Sprite::isComplete()
{
	return (fromLastSwitch_ == 0);
}


// -----------------------------------------------
// Name: T6_Sprite::setAutoSwitchFrame()
// Desc: To set this sprite's auto-switch-frame feature on or off.
// -----------------------------------------------
void T6_Sprite::setAutoSwitchFrame(bool isOn)
{
	autoSwitchFrame_ = isOn;

	if (!isOn) {
		FOR(synchronousSpriteList_.size())
			if (synchronousSpriteList_.at(i) == this)
				return;

		synchronousSpriteList_.push_back(this);
	}
}


// -----------------------------------------------
// Name: T6_Sprite::synchronousProcessToNextFrame()
// Desc: To process the sprite which is set to unable to process frame automatically.
// -----------------------------------------------
void T6_Sprite::synchronousProcessToNextFrame(double passedGameTime)
{
	FOR(synchronousSpriteList_.size())
		synchronousSpriteList_.at(i)->processToNextFrame(passedGameTime);
}


void T6_Sprite::setFrameTime(double newTime)
{
	switchFrameTime_ = newTime;
}


double T6_Sprite::getFrameTime()
{
	return switchFrameTime_;
}


T6_Sprite* T6_Sprite::clone() const
{
	return new T6_Sprite(*this);
}


void T6_Sprite::update()
{
	if (getTimeCode_() != timeCode_)
	{
		timeCode_ = getTimeCode_();
		timer_ += getRoundTime_();
		if (timer_ >= DEFAULT_FRAME_TIME)
		{
			defaultIndex_++;
			if (defaultIndex_ >= ((~0) >> 1))
			{
				defaultIndex_ = 0;
			}
		}
	}
}


void T6_Sprite::initialize(getInt getTimeCodeFunction, getDword getRoundTimeFunction)
{
	getTimeCode_ = getTimeCodeFunction;
	getRoundTime_ = getRoundTimeFunction;
	defaultIndex_ = 0;
	timeCode_ = 0;
	timer_ = 0;
}

getDword T6_Sprite::getRoundTime_;

getInt T6_Sprite::getTimeCode_;

DWORD T6_Sprite::timer_;

int T6_Sprite::timeCode_;

int T6_Sprite::defaultIndex_;
