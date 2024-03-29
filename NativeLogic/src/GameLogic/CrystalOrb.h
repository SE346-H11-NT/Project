#ifndef CrystalOrb_h__
#define CrystalOrb_h__

#include "MetalOrb.h"
#include "ShootObject.h"
#include "AutoAimingObject.h"

#define CRYSTAL_BOUND_SIZE	Size(16.0F, 16.0F)
#define CRYSTAL_AIMING_MEASURE	ANGLE_CLOCKWISE(1)
#define CRYSTAL_RESOURCE_LINK	(tstring(_T("Resource//Bosses//ShadowEntrance//CrystalOrb")) + EXTENSION_PICTURE)
#define CRYSTAL_RESOURCE_ROWS	1
#define CRYSTAL_RESOURCE_COLUMNS	1
#define CRYSTAL_SHOOT_DELAY	6000
#define CRYSTAL_LIFE_POINTS	50

class CrystalOrb :
	public MetalOrb,
	public ShootObject,
	public AutoAimingObject
{
public:
	CrystalOrb(T6Vec3 position, Object* target);
	virtual ~CrystalOrb();

	virtual void setBasicProperties();

	virtual int computeShootAngle();

	virtual T6Vec3 computeShootPoint();

	virtual void update();

	virtual void draw();

	virtual bool affect(Object* obj, DWORD key);

	virtual bool isTerminated();

	virtual void activateUpdate();

private:
	DWORD timeCounter_;
};

#endif // CrystalOrb_h__
