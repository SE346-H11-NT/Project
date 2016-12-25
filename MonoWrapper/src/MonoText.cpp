#include "Stdafx.h"
#include "MonoUtils.h"
#include "MonoText.h"

void MonoWrapper::Graphic::MonoText::drawText(const char* Content, int Position, int Color, int Size, int DT_Type)
{
	gcroot<System::String^> rootSTR = gcnew System::String(Content);
	WindowsFramework::Graphic::MText::drawText(rootSTR, Position, Color, DT_Type);
	SAFE_DEL_ROOT(rootSTR);
}