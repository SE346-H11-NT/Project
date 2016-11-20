#include "Selector.h"


T6_Texture* Selector::texture_ = nullptr;


Selector::Selector()
{
}


Selector::Selector(T6Vec3 position)
{
	position_ = position;
	currentSelection_ = 0;
	drawType_ = DRAW_ALL;
	isSelectedDraw_ = true;
	if (texture_ == nullptr)
	{
		texture_ = new T6_Texture(SELECTOR_RESOURCE_LINK.c_str());
	}
}


Selector::~Selector()
{
	SAFE_RELEASE(texture_);
	selection_.clear();
}


void Selector::assignSelection(const tchar* selectionName)
{
	selection_.push_back(selectionName);
}

void Selector::toNextSelection()
{
	currentSelection_ = (currentSelection_ + 1) % selection_.size();
}

void Selector::toPrevSelection()
{
	currentSelection_--;
	if (currentSelection_ < 0)
	{
		currentSelection_ = selection_.size() - 1;
	}
}

const tchar* Selector::getSelectionName()
{
	return selection_.at(currentSelection_);
}

int Selector::getSelectionIndex()
{
	return currentSelection_;
}

void Selector::draw(bool isDrawSelectorSign)
{
	T6Vec3 tempPos = position_;

	timer_ += Timer::getRoundTime();
	if (timer_ >= SELECTOR_FLASH_TIME)
	{
		timer_ = 0;
		if (drawType_ == FLASH_SELECTED)
			isSelectedDraw_ = !isSelectedDraw_;

	}

	FOR(selection_.size())
	{
		if (currentSelection_ == i)
		{
			if (isDrawSelectorSign)
				texture_->drawImage(tempPos + SELECTOR_DISTANCE_TO_SELECTOR_CENTER, nullptr, SCALE_NO, TRANSLATE_NO, DrawCenter::CENTER);

			if (!isSelectedDraw_)
			{
				tempPos += SELECTOR_DISTANCE_BETWEEN_SELECTION;
				continue;
			}
		}

		TEXT_CODE(FreeText::get().drawText(selection_.at(i), tempPos));

		tempPos += SELECTOR_DISTANCE_BETWEEN_SELECTION;
	}
}


const tchar* Selector::select()
{
	drawType_ = FLASH_SELECTED;
	return getSelectionName();
}


void Selector::setSelection(int index)
{
	currentSelection_ = index;
}

void Selector::reset()
{
	currentSelection_ = 0;
	drawType_ = DRAW_ALL;
	isSelectedDraw_ = true;
}
