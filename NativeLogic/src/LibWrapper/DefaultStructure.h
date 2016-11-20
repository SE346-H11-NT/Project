#ifndef __DEFAULT_STRUCTURE_H__
#define __DEFAULT_STRUCTURE_H__

#include <sstream>
#include <iostream>
using namespace std;

enum Direction
{
	NONE = -3,
	UP = 2,
	DOWN = -2,
	LEFT = -1,
	RIGHT = 1,
	NUM_OF_DIT6RectION = 4
};


enum Side
{
	SIDE_LEFT = 0,
	SIDE_RIGHT,
	NUM_OF_SIDE
};



// Locked by ExplodeBridge
enum DrawCenter
{
	TOPLEFT = 0,
	TOPRIGHT,
	BOTTOMCENTER,
	CENTER,
	BOTTOMLEFT,
	BOTTOMRIGHT,
	TOPCENTER,
	NUM_OF_DRAWCENTER
};



template<typename T = double>
union Vector2{

	T values[2];

	struct {
		T width;
		T height;
	};

	struct {
		T x;
		T y;
	};

	// Constructor
	Vector2(T first = 0, T second = 0)
	{
		values[0] = first;
		values[1] = second;
	}

	bool operator==(const int& value)
	{
		return (values[1] == value) && (values[2] == value);
	}

};

typedef Vector2<long> Size;

typedef unsigned int index_t;


// Multiple language structure type defination=========================
#ifdef UNICODE

typedef	std::wstring	tstring;
typedef std::wfstream	tfstream;
typedef wchar_t			tchar;
typedef wstringstream	tstringstream;

#define tmemset			wmemset
#define ttoi			_wtoi
#define tstrcpy			wcscpy_s

#else

typedef std::string		tstring;
typedef std::fstream	tfstream;
typedef char			tchar;
typedef ostringstream	tstringstream;

#define tmemset			memset
#define ttoi			atoi
#define tstrcpy			strcpy

#endif

#endif