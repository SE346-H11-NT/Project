#ifndef __DLL_IMPORTER__
#define __DLL_IMPORTER__

#include "BridgeUtils.h"

// MONO INCLUDE
#include "MonoTexture.h"
#define NativeTexture MonoWrapper::Graphic::MonoTexture

#include "MonoMatrix.h"
#define NativeMatrix MonoWrapper::DataType::MonoMatrix

#include "MonoVector.h"
#define NativeVec2 MonoWrapper::DataType::MonoVector2
#define NativeVec3 MonoWrapper::DataType::MonoVector3
#define NativeVec4 MonoWrapper::DataType::MonoVector4

#include "MonoRectangle.h"
#define NativeRect MonoWrapper::DataType::MonoRectangle

#endif // !__DLL_IMPORTER__
