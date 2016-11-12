#ifndef __DLL_IMPORTER__
#define __DLL_IMPORTER__

#include "BridgeUtils.h"
//#pragma comment(lib,"MonoWrapper.lib")

namespace MonoWrapper {
	namespace Graphic
	{
		class CBIMPORT MonoTexture
		{
		public:
			MonoTexture(const char* path);
			~MonoTexture();

			// TODO: merge param with T6Texture
			void draw();
		};
	}

	class CBIMPORT MonoFactory
	{
	public:
		static Graphic::MonoTexture* STDCALL createMonoTexture(const char* str);
		static void STDCALL destroyMonoTexture(Graphic::MonoTexture* instance);
	};
}

#define NativeFactory MonoWrapper::MonoFactory
#define NativeTexture MonoWrapper::Graphic::MonoTexture

#endif // !__DLL_IMPORTER__
