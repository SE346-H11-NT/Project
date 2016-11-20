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

#define PIXEL_TO_POINT96(A) ((A/2*72/96))
#define POINT_TO_PIXEL96(A) ((A*2*96/72))

#define DEFAULT_FONT_COLOR 0xFFBCBCBC

class T6_Text
{
public:
	T6_Text();
	~T6_Text(void);

	static void	setPositioncConvertMatrix(const T6Matrix4& newMatrix);


	// -----------------------------------------------
	// Name: T6_Text:drawText()
	// Desc: Draw any kind of object onto screen, base on passed position.
	// -----------------------------------------------
	template <class T> 
	void drawText(const T& Content, T6Vec3 Position, T6Color Color = DEFAULT_FONT_COLOR,
			 int Size = DEFAULT_FONTSIZE, UINT DT_Type = DT_LEFT, bool converted = true)
	{
#if ENABLE_TEXT
		if (Size != fontSize_)
			setFontSize(Size);

		T6Vec3 pos(Position);

		if (converted) {
			D3DXVec3TransformCoord(&pos, &pos, &cameraConvertMatrix_);
		}
		
		T6Rect drawField;

		drawField = { pos.x, pos.y, 0, 0 };

		font_->DrawText(spriteHandler_, Default::tostr(Content).c_str(),
			-1, &drawField, DT_CALCT6Rect, Color);

		if (DT_Type == DT_CENTER)
		{
			LONG w = drawField.right - drawField.left;
			drawField.left -= (LONG)(w / 2.0F);
			drawField.right -= (LONG)(w / 2.0F);
		}
		else if (DT_Type == DT_RIGHT)
		{
			LONG w = drawField.right - drawField.left;
			drawField.left -= w;
			drawField.right -= w;
		}

		font_->DrawText(spriteHandler_, Default::tostr(Content).c_str(),
			-1, &drawField, DT_Type, Color);
#endif
	}


	// -----------------------------------------------
	// Name: T6_Text:drawText()
	// Desc: Draw any kind of object onto screen, base on passed draw field.
	// -----------------------------------------------
	template <class T> 
	void drawText(const T& Content, T6Rect* drawField, T6Color Color = DEFAULT_FONT_COLOR,
		int Size = DEFAULT_FONTSIZE, UINT DT_Type = DT_LEFT)
	{
#if ENABLE_TEXT
		if (Size != m_fontSize)
			SetFontSize(Size);

		m_font->DrawText(*spriteHandler_, tostr(Content),
						-1, drawField, DT_Type,Color);
#endif
	}
	
private:
	void setFontSize(int newSize);
	void initializeFont();

private:
	static T6Matrix4 cameraConvertMatrix_;
	LPCTSTR fontFace_;
	int fontSize_;
};

#endif