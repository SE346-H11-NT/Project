#include "Stdafx.h"
#include "MonoTexture.h"
#include "MonoUtils.h"

MonoWrapper::Graphic::MonoTexture::MonoTexture(const char* path) 
	: m_path(path)
{
	gcroot<System::String^> rootSTR = gcnew System::String(path);
	m_ID = WindowsFramework::Graphic::MTexture::create(rootSTR);
	SAFE_DEL_ROOT(rootSTR);
}

MonoWrapper::Graphic::MonoTexture::MonoTexture(int id)
{
	m_ID = WindowsFramework::Graphic::MTexture::createCopy(id);
}

MonoWrapper::Graphic::MonoTexture::~MonoTexture()
{
	m_path = nullptr;
}

//void MonoWrapper::Graphic::MonoTexture::draw(DataType::MonoVector3 pos, DataType::MonoRectangle* srcRect, DataType::MonoVector2 scale,
//	DataType::MonoVector2 translate, DataType::MonoVector3 drawCenter, float angle, DataType::MonoVector4 color)
void MonoWrapper::Graphic::MonoTexture::draw(int pos, int srcRect, int scale,
	int translate, int drawCenter, float angle, int color)
{
	WindowsFramework::Graphic::MTexture::draw(
		m_ID,
		pos, 
		srcRect,
		scale, 
		translate, 
		drawCenter, 
		angle, 
		color);
}

const int MonoWrapper::Graphic::MonoTexture::getWidth() const
{
	return WindowsFramework::Graphic::MTexture::getWidth(m_ID);
}

const int MonoWrapper::Graphic::MonoTexture::getHeight() const
{
	return WindowsFramework::Graphic::MTexture::getHeight(m_ID);
}