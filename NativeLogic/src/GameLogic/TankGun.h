#ifndef TankGun_h__
#define TankGun_h__

#include "Mobs.h"
#include "ShootObject.h"
#include "AutoAimingObject.h"
#include "MoveObject.h"

#define GUN_RESOURCE_LINK	(tstring(_T("Resource//Mobs//Tank//Gun")) + EXTENSION_PICTURE)
#define GUN_RESOURCE_ROWS	3
#define GUN_RESOURCE_COLUMNS	2
#define GUN_AIMING_MEASURE	(22.5F)
#define GUN_ROTATE_DELAY	DEFAULT_FRAME_TIME
#define GUN_SHOOT_DELAY		2000
#define GUN_BULLET_ROW		3	// num of bullets in a shoot row
#define GUN_STATUS_BY_AIM_ANGLE_AND_SCALEX(angle, scaleX)	((scaleX > 0 ? -1: 1) * \
															(angle / GUN_AIMING_MEASURE + 0.5) - \
															(scaleX < 0 ? 8 : 0))
#define GUN_SHOOTPOINTS_FIX	T6Vec3 shootPointFixes[] = {T6Vec3(23.0F, -4.0F, 0.0F),	\
															 T6Vec3(18.0F, -15.0F, 0.0F),	\
															 T6Vec3(14.0F, -21.0F, 0.0F)}

class TankGun :
	public Mobs,
	public ShootObject,
	public AutoAimingObject,
	public MoveObject
{
public:
	TankGun(T6Vec3 pos, Object* theHost, Object* target);
	virtual ~TankGun();

	virtual unsigned int getScore();

	virtual void draw();

	virtual void waitUpdate();

	virtual void activateUpdate();

	virtual void deadUpdate();

	virtual bool affect(Object* obj, DWORD key);

	virtual void setBasicProperties();

	virtual void deadEffect();

	virtual void update();

	virtual bool isTerminated();

	virtual int computeShootAngle();

	virtual T6Vec3 computeShootPoint();

	void setColor(DWORD color);

private:
	Object* theHost_;
	Object* target_;
	DWORD fadeColor_;
	DWORD rotateTimeCounter_;
	DWORD shootDelay_;
	int bulletCounter_;
	T6Vec3 distance_;
};

#endif // TankGun_h__
