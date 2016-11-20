#ifndef FloatingBulletBag_h__
#define FloatingBulletBag_h__

#include "DestroyableObject.h"
#include "MoveObject.h"
#include "BulletFalcon.h"
#include "Map.h"

#define FLOATING_BULLET_BAG_SIZE				Size(24.0, 16.0)
#define FLOATING_BULLET_BAG_LINK				(tstring(_T("Resource//Miscellaneous//FloatingBulletBag")) + EXTENSION_PICTURE)
#define FLOATING_BULLET_BAG_RESOURCE_ROWS		1
#define FLOATING_BULLET_BAG_RESOURCE_COLUMNS	1
#define FLOATING_BULLET_REDIT6RectING_SPEED		(360.0)
#define FLOATING_BULLET_REDIT6RectING_CAP			(100.0)
#define FLOATING_BULLET_BAG_MOVE_SPEED			(DEFAULT_MOVE_SPEED)

enum FloatingBulletBagStatus
{
	FBS_WAIT = 0,
	FBS_FLY
};

#define AXIS_X 0
#define AXIS_Y 1

class FloatingBulletBag : public virtual DestroyableObject
						, public virtual MoveObject
{
public:
	FloatingBulletBag(T6Vec3 position, BulletFalconType containFalconType, T6Vec3 velocity);
	virtual ~FloatingBulletBag();

	virtual void update();

	virtual void setBasicProperties();

	virtual void draw();

	virtual void deadEffect();

	virtual bool affect(Object* obj, DWORD key);

	virtual bool isTerminated();

			T6Vec3 computeVelocity();

private:
	BulletFalconType containFalconType_;
	bool isTerminated_;
	int currentDirectAngle_;
	FloatingBulletBagStatus bagState_;
	int flyStraightAxis_;
};

#endif // FloatingBulletBag_h__
