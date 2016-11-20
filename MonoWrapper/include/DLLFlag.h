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
NOT_EXPORT_CODE(\
	public:\
		ClassName(const gcroot <NativeClassName^> rawData);\
		gcroot <NativeClassName^> getRawData();\
	private:\
		gcroot <NativeClassName^>	m_rawData; \
)

#define MONO_DEFINATION(ClassName, NativeClassName)	\
ClassName::ClassName()\
{\
	m_rawData = gcnew NativeClassName();\
}\
ClassName::~ClassName()\
{\
	SAFE_DEL_ROOT(m_rawData);\
}\
ClassName::ClassName(const gcroot<NativeClassName^> rawData)\
	: m_rawData(rawData)\
{\
}\
gcroot<NativeClassName^> ClassName::getRawData()\
{\
	return m_rawData;\
}

#endif //__DLLFLAG__