#ifndef __DLLFLAG__
#define __DLLFLAG__

extern "C"
{
#if defined(MONO_API_EXPORT)
#define MONOAPI	__declspec(dllexport)
#define MONOCODE(code)	code
#endif

#if defined(MONO_API_IMPORT)
#define MONOAPI	__declspec(dllimport)
#define MONOCODE(code)
#endif
}

#if defined(MONO_API_EXPORT)
#define NOT_EXPORT_CODE(code)	code
#else
#define NOT_EXPORT_CODE(code)
#endif

#define MONO_DECLARE(ClassName, NativeClassName)	\
	public:\
		ClassName();\
		~ClassName();\
	public:\
		ClassName::ClassName(const ClassName& obj);\
		int getID();\
	private:\
		int m_ID;

#define MONO_DEFINATION(ClassName, NativeClassName)	\
ClassName::ClassName()\
	: m_ID(-1)\
{}\
ClassName::~ClassName()\
{\
	m_ID = -1;\
}\
ClassName::ClassName(const ClassName& obj)\
{\
	m_ID = NativeClassName::createCopy(obj.m_ID);\
}\
int ClassName::getID()\
{\
	return m_ID;\
}

#endif //__DLLFLAG__