#ifndef __DEFAULT_CONSTANT_H__
#define __DEFAULT_CONSTANT_H__

#include <tchar.h>
#include "../Generic/GenericDatatype.h"

#define ENABLE_TEXT	0
#define ENABLE_SOUND 0
#define ENDABLE_CONTROLLER 0

#if ENABLE_TEXT
#define TEXT_CODE(code)	code
#else
#define TEXT_CODE(code)
#endif

#if ENABLE_SOUND
#define SOUND_CODE(code)	code
#else
#define SOUND_CODE(code)
#endif

#if ENDABLE_CONTROLLER
#define CONTROLLER_CODE(code)	code
#else
#define CONTROLLER_CODE(code)
#endif

// System setting
#define RESOLUTION_WIDTH		256
#define RESOLUTION_HEIGHT		240
#define SCREEN_WIDTH			1024
#define SCREEN_HEIGHT			600
#define DEFAULT_DEPTH			0.0f
#define DEFAULT_FRAME_TIME		17.0

// Specify position in game world displayed on screen.
#define GAMEPOS_CENTER			(T6Vec3(RESOLUTION_WIDTH / 2.0F,	RESOLUTION_HEIGHT / 2.0F,		DEFAULT_DEPTH))
#define GAMEPOS_NOTIFY			(T6Vec3(RESOLUTION_WIDTH / 2.0F,	RESOLUTION_HEIGHT / 4.0F * 3,	DEFAULT_DEPTH))
#define GAMEPOS_BOTTOM_CENTER	(T6Vec3(RESOLUTION_WIDTH / 2.0F,	0.0F,							DEFAULT_DEPTH))
#define GAMEPOS_BOTTOM_RIGHT	(T6Vec3(RESOLUTION_WIDTH,			0.0F,							DEFAULT_DEPTH))
#define GAMEPOS_BOTTOM_LEFT		(T6Vec3(0.0F,						0.0F,							DEFAULT_DEPTH))
#define GAMEPOS_TOP_LEFT		(T6Vec3(0.0F,						RESOLUTION_HEIGHT,				DEFAULT_DEPTH))
#define GAMEPOS_TOP_CENTER		(T6Vec3(RESOLUTION_WIDTH / 2.0F,	RESOLUTION_HEIGHT,				DEFAULT_DEPTH))

// Default text setting.
#define DEFAULT_FONTSIZE	8
#define DEFAULT_FONTFACE	_T("Contra (Famicom/NES)")
#define DEFAULT_FONTPATH	_T("Resource\\font.ttf")

// maps unsigned 8 bits/channel to T6Color
#if 1
#define COLOR_HEXA(a,r,g,b) ((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff))
#define COLOR_HEXA_RGB(r,g,b)   COLOR_HEXA(0xff,r,g,b)
#else
#define COLOR_HEXA(a,r,g,b)		T6Color((float)r, (float)g, (float)b, (float)a)
#define COLOR_HEXA_RGB(r,g,b)   COLOR_HEXA(0xff,r,g,b)
#endif

// Specify colors.
#define COLOR_NO			COLOR_HEXA_RGB(255,	255,	255)
#define COLOR_WHITE			COLOR_HEXA_RGB(255,	255,	255)
#define COLOR_BLACK			COLOR_HEXA_RGB(0,	0,		0)

// About zoom macros.
static const T6Vec2 SCALE_NO		= T6Vec2(1.0F, 1.0F);
static const T6Vec2 SCALE_FLIP_X	= T6Vec2(-1.0F, 1.0F);
static const T6Vec2 SCALE_FLIP_Y	= T6Vec2(1.0F, -1.0F);
static const T6Vec2 SCALE_FLIP_XY	= T6Vec2(-1.0F, -1.0F);
#define SCALE_A(A)					  T6Vec2(A, A)
#define SCALE_XY(A, B)				  T6Vec2(A, B)
#define SCALE_VELO_X(A)				  T6Vec2(A != 0? (float)A/fabs(A) : 1.0F, 1.0F)

// Define to fast change a vector.
#define FLIP_Y(vector3)		(T6Vec3(vector3.x, -vector3.y, vector3.z))
#define FLIP_X(vector3)		(T6Vec3(-vector3.x, vector3.y, vector3.z))

// Simple functions
#define MAX(A, B)			(A > B ? A : B)
#define MIN(A, B)			(A < B ? A : B)
#define MAX_ABS(A, B)		(fabs(A) > fabs(B) ? A : B)
#define MIN_ABS(A, B)		(fabs(A) < fabs(B) ? A : B)

// Translating macro.
static const T6Vec2 TRANSLATE_NO	= T6Vec2(0.0f, 0.0f);

// Simple definition For-loop macros.
#define FOR(A)				for(decltype(A) i = 0; i < (A); ++i)
#define FOR_e(A)			for(int i = 0; i < (A); ++i)
#define DFOR(A)				for(int i = (A); i >= 0; --i)
#define FORJ(A)				for(auto j = (A) - (A); j < (A); ++j)
#define FOR_A(start,stop)	for(auto i = start; i != stop; ++i)
#define FOR_AB(A, B)		for(auto i = (A); i < (B); ++i)

// Safe delete pointer macro.
#define SAFE_RELEASE(A)		{if (A) {delete A; A = 0;}}

#define ASSIGN_PTR(ptr, value) {if (ptr != nullptr) {*ptr = value;}}

#define	ANGLE_TO_RADIAN(angle)	(angle / 180.0 * PI)

#if _WIN32 || _WIN64
#include <windows.h>
#include <ostream>
#include <sstream>
#define WARNING_BOX(A)		MessageBox(0, (static_cast<std::ostringstream&>(std::ostringstream() << __FILE__ << std::endl << __LINE__ << std::endl << __FUNCTION__ << std::endl << A)).str().c_str(), _T("Error"), MB_OK)
#else
#define WARNING_BOX(A)
#endif

#endif