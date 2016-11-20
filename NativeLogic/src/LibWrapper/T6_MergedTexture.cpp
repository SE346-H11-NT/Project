#include "T6_MergedTexture.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif


T6_MergedTexture::T6_MergedTexture(const tchar* path, int nColumns, int nRows) : T6_Texture(path)
{
	this->rows_ = nRows;
	this->columns_ = nColumns;
	
	imageRectCache_ = new T6Rect*[(rows_ * columns_)];
	FOR((rows_ * columns_))
		imageRectCache_[i] = nullptr;
}


T6_MergedTexture::T6_MergedTexture(const T6_MergedTexture& sourceMTexture) : T6_Texture(sourceMTexture)
{
	this->rows_ = sourceMTexture.rows_;
	this->columns_ = sourceMTexture.columns_;

	imageRectCache_ = new T6Rect*[(rows_ * columns_)];
	this->frameSize_ = sourceMTexture.frameSize_;
	FOR((rows_ * columns_))
		imageRectCache_[i] = sourceMTexture.imageRectCache_[i];
}


T6_MergedTexture::~T6_MergedTexture()
{
	FOR(rows_ * columns_)
		SAFE_RELEASE(imageRectCache_[i]);

	SAFE_RELEASE(imageRectCache_);
}


void T6_MergedTexture::loadMergedTexture()
{
	T6_Texture::loadImageFromStoredInfo();

	this->frameSize_.width = this->getWidth() / columns_;
	this->frameSize_.height = this->getHeight() / rows_;
}


void T6_MergedTexture::draw(index_t index, T6Vec3 position, DrawCenter drawCenter,
							T6Vec2 scale, T6Vec2 translate, float angle, T6Color fadedColor)
{
	if (!isLoaded()) {
		loadMergedTexture();
	}

	if (index == DEFAULT_INDEX)
	{
		index = defaultIndex_;
	}

	T6_MergedTexture::update();

	index_t indexrow = (index_t)(index / columns_);
	index_t indexcol = (index_t)(index % columns_);

	if (imageRectCache_[index] == nullptr) {
		imageRectCache_[index]			= new T6Rect();
		imageRectCache_[index]->left	= (LONG)(indexcol * frameSize_.width);
		imageRectCache_[index]->right	= (LONG)(imageRectCache_[index]->left + frameSize_.width);
		imageRectCache_[index]->top		= (LONG)(indexrow * frameSize_.height);
		imageRectCache_[index]->bottom	= (LONG)(imageRectCache_[index]->top + frameSize_.height);
	}

	drawImage(position, imageRectCache_[index], scale, translate, drawCenter, angle, fadedColor);
}

void T6_MergedTexture::draw(index_t index, T6Vec3 position, float percentOfVisible_width, float percentOfVisible_height, bool	isTranslateXAxis,
	DrawCenter drawCenter /*= DrawCenter::TOPLEFT*/, T6Vec2 scale /*= SCALE_NO*/, T6Vec2 translate /*= TRANSLATE_NO*/, float angle /*= ANGLE_NO*/, T6Color fadedColor /*= 0xFFFFFFFF*/)
{
	if (!isLoaded()) {
		loadMergedTexture();
	}

	T6_MergedTexture::update();

	if (index == DEFAULT_INDEX)
	{
		index = defaultIndex_;
	}

	index_t indexrow = (index_t)(index / columns_);
	index_t indexcol = (index_t)(index % columns_);

	if (imageRectCache_[index] == 0) {
		imageRectCache_[index] = new T6Rect();
		imageRectCache_[index]->left = (LONG)(indexcol * frameSize_.width);
		imageRectCache_[index]->right = (LONG)(imageRectCache_[index]->left + frameSize_.width);
		imageRectCache_[index]->top = (LONG)(indexrow * frameSize_.height);
		imageRectCache_[index]->bottom = (LONG)(imageRectCache_[index]->top + frameSize_.height);
	}

	T6Rect drawRect(*imageRectCache_[index]);
	convertVisiblePercent(percentOfVisible_width, percentOfVisible_height, drawRect, position, isTranslateXAxis, scale);

	drawImage(position, &drawRect, scale, translate, drawCenter, angle, fadedColor);
}


Size T6_MergedTexture::getFrameSize()
{
	if (!isLoaded())
		loadMergedTexture();

	return frameSize_;
}


T6_MergedTexture* T6_MergedTexture::clone() const
{
	return new T6_MergedTexture(*this);
}


void T6_MergedTexture::initialize(getInt getTimeCodeFunction, getDword getRoundTimeFunction)
{
	getTimeCode_ = getTimeCodeFunction;
	getRoundTime_ = getRoundTimeFunction;
	defaultIndex_ = 0;
	timeCode_ = 0;
	timer_ = 0;
}


void T6_MergedTexture::update()
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

getDword T6_MergedTexture::getRoundTime_;

getInt T6_MergedTexture::getTimeCode_;

DWORD T6_MergedTexture::timer_;

int T6_MergedTexture::timeCode_;

int T6_MergedTexture::defaultIndex_;
