#include "FreeText.h"


FreeText* FreeText::instance_ = nullptr;


FreeText::FreeText()
{
#if ENABLE_TEXT
	if (spriteHandler_ != nullptr && device_ != nullptr)
	{
		textHandler_ = new T6_Text(device_, spriteHandler_);
	}
	else
		WARNING_BOX(WARNING_INITIALIZE_FREE_TEXT);
#endif
}


FreeText::~FreeText()
{
}


FreeText& FreeText::get()
{
	if (instance_ == nullptr)
	{
		instance_ = new FreeText();
	}

	return *instance_;
}
