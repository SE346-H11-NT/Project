#ifndef __TILE_H__
#define __TILE_H__

#include "MoveObject.h"
#include "Pretties.h"

#include "DefaultStructure.h"
#include "DefaultMethods.h"
#include "T6_MergedTexture.h"


enum TileType {
	TOP_ONLY = 0,
	TOP_UNDROP,
	FOUR_FACE,
	FOUR_DESTROYABLE,
	FOUR_IMMORTAL,
	NUM_OF_TILE_TYPE
};

class Tile : virtual public Object
{
public:
	Tile();
	Tile(long left, long right, long top, long bottom,
		int characterTouch, TileType type);
	virtual ~Tile();
	virtual void		update();
	virtual void		draw();
			void		pushAPretties(Pretties* newPretties);
			TileType	getType();
			int			getTouchedStatus();
	virtual T6Rect		getRect();
	virtual void		activate();
			bool		isWater();

			virtual void setBasicProperties();
			
			virtual bool  affect(Object* obj, DWORD key);
			virtual bool  affect(Object* obj, DWORD key, TileType collisLevel);

			virtual bool isTerminated();

protected:
	vector<const Pretties*> linkedPretties_;

private:
	TileType type_;
	int characterTouch_;
};

#endif