#ifndef FreeText_h__
#define FreeText_h__

#include "T6_Text.h"
#include "GameDefaultConstant.h"

class FreeText
{
public:
	//static void initialize(LPDIT6Rect3DDEVICE9& d3dDevice, LPD3DXSPRITE& spriteHandler);

	template <class T>
	void drawText(const T& Content, T6Vec3 Position, T6Color Color = DEFAULT_FONT_COLOR,
		int Size = DEFAULT_FONTSIZE, int DT_Type = DT_LEFT)
	{
		textHandler_->drawText(Content, Position, Color, Size, DT_Type);
	}

	static FreeText& get();

private:
	FreeText();
	~FreeText();

private:
	T6_Text* textHandler_;
	static FreeText* instance_;
	//static LPDIT6Rect3DDEVICE9 device_;
	//static LPD3DXSPRITE spriteHandler_;
};

#endif // FreeText_h__
