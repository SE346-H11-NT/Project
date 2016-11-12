#ifndef __MONO_UTILS__
#define __MONO_UTILS__

#ifndef __GENERIC_UTILS__
#define __GENERIC_UTILS__
#define SAFE_DEL(ptr)	if(ptr){delete ptr; ptr = nullptr;}
#define MONOEXPORT __declspec(dllexport)
#define STDCALL	__stdcall
#endif // __GENERIC_UTILS__

#endif //__MONO_UTILS__