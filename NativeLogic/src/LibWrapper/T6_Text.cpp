#include "T6_Text.h" 

T6Matrix4 T6_Text::cameraConvertMatrix_;

// -----------------------------------------------
// Name: T6_Text:T6_Text()
// Desc: Set the basic PROPERTIES such as font name, size, device to draw.
// -----------------------------------------------
T6_Text::T6_Text()
{
#if ENABLE_TEXT
	d3dDevice_		= d3dDevice;
	fontFace_		= DEFAULT_FONTFACE;
	fontSize_		= DEFAULT_FONTSIZE;
	spriteHandler_	= spriteHandler;
	T6Matrix4Identity(&cameraConvertMatrix_);

	AddFontResourceEx(DEFAULT_FONTPATH, FR_PRIVATE, 0);

	initializeFont();
#endif
}


// -----------------------------------------------
// Name: T6_Text:initializeFont()
// Desc: Create a new font suit with current PROPERTIESs.
// -----------------------------------------------
void T6_Text::initializeFont()
{
#if ENABLE_TEXT
	D3DXCreateFont(
		d3dDevice_,
		fontSize_,
		0,400,0,false,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_PITCH,
		fontFace_
		,&font_);
#endif
}


// -----------------------------------------------
// Name: T6_Text:setFontSize()
// Desc: Set a new size for the font (processed in Points).
// -----------------------------------------------
void T6_Text::setFontSize(int newSize)
{
#if ENABLE_TEXT
	font_->Release();
	fontSize_ = newSize;
	initializeFont();
#endif
}


// -----------------------------------------------
// Name: T6_Text:~T6_Text()
// Desc: Release Text-draw object after use (close Game).
// -----------------------------------------------
T6_Text::~T6_Text(void)
{
#if ENABLE_TEXT
	font_->Release();
	RemoveFontResource(DEFAULT_FONTPATH);
#endif
}


// -----------------------------------------------
// Name: T6_Text:setPositioncConvertMatrix()
// Desc: Setted new matrix to convert draw text position.
// -----------------------------------------------
void T6_Text::setPositioncConvertMatrix(const T6Matrix4& newMatrix)
{
	T6_Text::cameraConvertMatrix_ = newMatrix;
}