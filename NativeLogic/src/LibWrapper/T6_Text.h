//==============================
// Last change: 27/9/2014
// T6_Framework
// T6_Text v1.0
// With this class, you can define a text-processing object, which allow you
// to draw text onto your windows.
//==============================
#ifndef __TEXT_H__
#define __TEXT_H__

#include <string>
#include <iostream>
#include <Windows.h>

#include "DefaultConstant.h"
#include "DefaultStructure.h"
#include "DefaultMethods.h"

#include "CSharpBridge/DLLImporter.h"

#define PIXEL_TO_POINT96(A) ((A/2*72/96))
#define POINT_TO_PIXEL96(A) ((A*2*96/72))

#define DEFAULT_FONT_COLOR 0xFFBCBCBC

class T6_Text
{
public:
	T6_Text();
	~T6_Text(void);

	// -----------------------------------------------
	// Name: T6_Text:drawText()
	// Desc: Draw any kind of object onto screen, base on passed position.
	// -----------------------------------------------
	template <class T> 
	//void drawText(const T& Content, T6Vec3 Position, T6Color Color = DEFAULT_FONT_COLOR,
	//	int Size = DEFAULT_FONTSIZE, UINT DT_Type = DT_LEFT, bool converted = true)
	void drawText(const T& Content, T6Vec3 Position, T6Color Color,
			 int Size, int DT_Type)
	{
		Position *= cameraConvertMatrix_;

#if ENABLE_TEXT
		WrappedText::drawText(Default::tostr(Content).c_str(), Position.getID(), Color.getID(), Size, DT_Type);
#endif
	}

	static void setPositioncConvertMatrix(const T6Matrix4& newMatrix);

	
private:
	void setFontSize(int newSize);
	void initializeFont();

private:
	static T6Matrix4	cameraConvertMatrix_;
};

#endif