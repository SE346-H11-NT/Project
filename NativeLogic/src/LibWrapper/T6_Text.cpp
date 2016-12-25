#include "T6_Text.h" 
T6Matrix4	T6_Text::cameraConvertMatrix_;

// -----------------------------------------------
// Name: T6_Text:T6_Text()
// Desc: Set the basic PROPERTIES such as font name, size, device to draw.
// -----------------------------------------------
T6_Text::T6_Text()
{
}


// -----------------------------------------------
// Name: T6_Text:initializeFont()
// Desc: Create a new font suit with current PROPERTIESs.
// -----------------------------------------------
void T6_Text::initializeFont()
{
}


// -----------------------------------------------
// Name: T6_Text:~T6_Text()
// Desc: Release Text-draw object after use (close Game).
// -----------------------------------------------
T6_Text::~T6_Text(void)
{
}

void T6_Text::setPositioncConvertMatrix(const T6Matrix4& newMatrix)
{
	T6_Text::cameraConvertMatrix_ = newMatrix;
}