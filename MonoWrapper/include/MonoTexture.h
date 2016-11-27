#ifndef __MONO_TEXTURE__
#define __MONO_TEXTURE__

#include "DLLFlag.h"

#if defined(MONO_API_EXPORT)
#include <msclr/auto_gcroot.h>
using namespace System;
using namespace WindowsFramework::Graphic;
#endif

#include "MonoVector.h"
#include "MonoRectangle.h"

extern "C"
{
	namespace MonoWrapper {
		namespace Graphic
		{
			class MONOAPI MonoTexture
			{
			public:
				MonoTexture(const char* path);
				MonoTexture(int id);
				~MonoTexture();

				// TODO: merge param with T6Texture
				//void draw(DataType::MonoVector3 pos, DataType::MonoRectangle* srcRect, DataType::MonoVector2 scale,
				//	DataType::MonoVector2 translate, DataType::MonoVector3 drawCenter, float angle, DataType::MonoVector4 color);
				void MonoWrapper::Graphic::MonoTexture::draw(int pos, int srcRect, int scale,
					int translate, int drawCenter, float angle, int color);
				const int getWidth() const;
				const int getHeight() const;

			private:
				const char* m_path;
				int m_ID;
			};
		}
	}
}
#endif //__MONO_TEXTURE__