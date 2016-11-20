#ifndef FloatingRock_h__
#define FloatingRock_h__

#include "Tile.h"
#include "MoveObject.h"

#define FLOATING_ROCK_RESOURCE_LINK	(tstring(_T("Resource//Miscellaneous//FloatingRock")) + EXTENSION_PICTURE)
#define FLOATING_ROCK_RESOURCE_ROWS	1
#define FLOATING_ROCK_RESOURCE_COLUMNS	1
#define FLOATING_ROCK_BOUND_SIZE	Size(32.0, 16.0)

class FloatingRock :
	public Tile,
	public MoveObject
{
public:
	FloatingRock(T6Vec3 position, T6Vec3 velocity, T6Rect moveRange);
	virtual ~FloatingRock();

	virtual void update();

	virtual void draw();

	virtual void setBasicProperties();

	virtual bool affect(Object* obj, DWORD key);

	virtual bool affect(Object* obj, DWORD key, TileType collisLevel);

	virtual bool isTerminated();

	virtual T6Vec3* getVelo();

private:
	T6Rect moveRange_;
	DWORD frameTime_;
};

#endif // FloatingRock_h__
