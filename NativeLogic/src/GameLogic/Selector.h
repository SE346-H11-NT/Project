#ifndef Selector_h__
#define Selector_h__

#include "GameDefaultConstant.h"
#include "FreeText.h"
#include "Timer.h"

#include "T6_Texture.h"
#include "T6_Text.h"

#include <vector>

#define SELECTOR_RESOURCE_LINK	(tstring(_T("Resource//Miscellaneous//Selector")) + EXTENSION_PICTURE)
#define SELECTOR_RESOURCE_ROWS	1
#define SELECTOR_RESOURCE_COLUMNS	1
#define SELECTOR_DISTANCE_TO_SELECTOR_CENTER	T6Vec3(-12.0F, -4.0F, 0.0F)
#define SELECTOR_DISTANCE_BETWEEN_SELECTION	T6Vec3(0.0F, -16.0F, 0.0F)
#define SELECTOR_FLASH_TIME	300

enum SelectorDrawType
{
	DRAW_ALL = 0,
	FLASH_SELECTED,
	NUM_OF_DRAW_TYPE
};

class Selector
{
public:
	Selector();
	Selector(T6Vec3 position);
	~Selector();

	void assignSelection(const tchar* selectionName);

	void toNextSelection();

	void toPrevSelection();

	void setSelection(int index);

	const tchar* select();

	const tchar* getSelectionName();

	int getSelectionIndex();

	void draw(bool isDrawSelectorSign);

	void reset();

private:
	static T6_Texture* texture_;
	T6Vec3 position_;
	int currentSelection_;
	vector<const tchar*> selection_;
	DWORD timer_;
	bool isSelectedDraw_;
	SelectorDrawType drawType_;
};

#endif // Selector_h__
