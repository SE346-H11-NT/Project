#include "Stdafx.h"
#include "MonoTexture.h"
#include "MonoUtils.h"

MonoWrapper::Graphic::MonoTexture::MonoTexture(const char* path) : m_texture(nullptr)
, m_path(nullptr)
{
	m_path = gcnew System::String(path);
	m_texture = gcnew MTexture(m_path);
}

MonoWrapper::Graphic::MonoTexture::~MonoTexture()
{
	SAFE_DEL_ROOT(m_path);
	SAFE_DEL_ROOT(m_texture);
}

void MonoWrapper::Graphic::MonoTexture::draw(DataType::MonoVector3 pos, DataType::MonoRectangle srcRect, DataType::MonoVector2 scale,
	DataType::MonoVector2 translate, DataType::MonoVector3 drawCenter, float angle, DataType::MonoVector4 color)
{
	m_texture->draw(
		pos.getRawData(), 
		srcRect.getRawData(), 
		scale.getRawData(), 
		translate.getRawData(), 
		drawCenter.getRawData(), 
		angle, 
		color.getRawData());
}

const int MonoWrapper::Graphic::MonoTexture::getWidth() const
{
	return m_texture->getWidth();
}

const int MonoWrapper::Graphic::MonoTexture::getHeight() const
{
	return m_texture->getHeight();
}
