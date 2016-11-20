#ifndef __GAME_UTILS__
#define __GAME_UTILS__

#include "../CSharpBridge/DLLImporter.h"

#ifndef __GENERIC_UTILS__
#define __GENERIC_UTILS__
#define SAFE_DEL(ptr)	if(ptr){delete ptr; ptr = nullptr;}
#endif // !__GENERIC_UTILS__

#endif // !__GAME_UTILS__
