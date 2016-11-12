#include "Stdafx.h"
#include "MonoTexture.h"

MonoWrapper::Graphic::MonoTexture::MonoTexture(const char* path) : m_texture(nullptr)
, m_path(nullptr)
{
	m_path = gcnew System::String(path);
	m_texture = gcnew MTexture(m_path);
}

MonoWrapper::Graphic::MonoTexture::~MonoTexture()
{
	SAFE_DEL(m_path);
	SAFE_DEL(m_texture);
}

void MonoWrapper::Graphic::MonoTexture::draw()
{
	m_texture->draw();
}