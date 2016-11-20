#ifndef __STAND_CANON_H__
#define __STAND_CANON_H__

#include "Mobs.h"
#include "ShootObject.h"
#include "AutoAimingObject.h"

#define STAND_CANON_NUM_OF_DIT6RectION 12
#define STAND_CANON_DIT6RectION_MEASURE	(360 / STAND_CANON_NUM_OF_DIT6RectION)
#define STAND_CANON_CHECK_IF_SHOOT_ANGLE(angle) (180 >= angle && angle > 90)
#define STAND_CANON_SHOOT_DISTANCE	(RESOLUTION_WIDTH / 3.0)
#define STAND_CANON_NUM_OF_MAP_COLOR	2
#define STAND_CANON_NUM_OF_LIGHT_COLOR	4
#define STAND_CANON_LIGHT_TIME		(DEFAULT_FRAME_TIME * 2)

#define LINK_STAND_CANON				_T("Resource//Mobs//StandCanon//StandCanon")
#define STAND_CANON_RESOURCE_LINK		(tstring(LINK_STAND_CANON) + EXTENSION_PICTURE)

#define STAND_CANON_BOUND_SIZE			Size(32.0, 32.0)
#define STAND_CANON_MAX_BULLET_IN_A_ROW	3
#define STAND_CANON_HEALTH_POINTS		10
#define STAND_CANON_RELOAD_TIME			5000
#define STAND_CANON_SHOOT_TIME			4000
#define STAND_CANON_ACTIVATE_TIME		(DEFAULT_FRAME_TIME * 2)

enum StandCanonStatus {
	APPEAR_30_PERCENT = 1,
	APPEAR_60_PERCENT,
	APPEAR_COMPLETLY,
	NUM_OF_SC_STATUS = 3
};

class StandCanon :
	public Mobs,
	public AutoAimingObject,
	public ShootObject
{
public:
	StandCanon(T6Vec3 position, Object* target);
	~StandCanon();

	virtual unsigned int getScore();

	virtual void draw();

	virtual void waitUpdate();

	virtual void activateUpdate();

	virtual void deadUpdate();

	virtual void setBasicProperties();

	virtual void deadEffect();

	virtual void update();

	virtual int computeShootAngle();

	virtual T6Vec3 computeShootPoint();

private:
	void rollUpdate();
	void shootUpdate();

	virtual bool  affect(Object* obj, DWORD key);

	virtual bool isTerminated();

private:
	T6Vec3 position_;
	static DWORD lightColor_[];
		   int lightTime_;
		   int timeCounter_;
	static int currentColor_;
	DWORD rotateDelay_;
	int shootDirection_;
	vector<Bullet*> shootedBullets_;
};

#endif