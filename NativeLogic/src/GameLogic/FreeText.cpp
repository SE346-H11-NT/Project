#include "FreeText.h"


FreeText* FreeText::instance_ = nullptr;


FreeText::FreeText()
{
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
