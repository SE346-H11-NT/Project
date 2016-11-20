#ifndef __MONO_UTILS__
#define __MONO_UTILS__

#ifndef __GENERIC_UTILS__
#define __GENERIC_UTILS__
#define SAFE_DEL(ptr)	if(ptr != nullptr){delete ptr; ptr = nullptr;}
#define SAFE_DEL_ROOT(ptr)	if(System::Object::ReferenceEquals(ptr, nullptr)){delete ptr; ptr = nullptr;}
#define STDCALL	__stdcall
#endif // __GENERIC_UTILS__

#endif //__MONO_UTILS__