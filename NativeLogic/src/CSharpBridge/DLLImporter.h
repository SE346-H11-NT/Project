#ifndef __DLL_IMPORTER__
#define __DLL_IMPORTER__

#include "BridgeUtils.h"

// MONO INCLUDE
#include "MonoTexture.h"
#define WrappedTexture MonoWrapper::Graphic::MonoTexture

#include "MonoText.h"
#define WrappedText MonoWrapper::Graphic::MonoText

#include "MonoKeyboard.h"
#define WrappedKeyboard MonoWrapper::Controller::MonoKeyboard

#include "MonoMatrix.h"
#define WrappedMatrix MonoWrapper::DataType::MonoMatrix

#include "MonoVector.h"
#define WrappedVec2 MonoWrapper::DataType::MonoVector2
#define WrappedVec3 MonoWrapper::DataType::MonoVector3
#define WrappedVec4 MonoWrapper::DataType::MonoVector4

#include "MonoRectangle.h"
#define WrappedRect MonoWrapper::DataType::MonoRectangle

#endif // !__DLL_IMPORTER__
