#ifndef StandShooter_h__
#define StandShooter_h__

#include "Mobs.h"
#include "ShootObject.h"

#define STAND_SHOOTER_RESOURCE_LINK	(tstring(_T("Resource//Mobs//StandShooter")) + EXTENSION_PICTURE)
#define STAND_SHOOTER_RESOURCE_ROWS	1
#define STAND_SHOOTER_RESOURCE_COLUMNS	2
#define STAND_SHOOTER_SHOOTPOINT_FIX	T6Vec3(16.0F, 24.0F, 0.0F)
#define SCORE_STAND_SHOOTER		500
#define STAND_SHOOTER_SHOOT_DELAY	3000	// 3s
#define STAND_SHOOTER_LIFE_POINTS	20
#define STAND_SHOOTER_BOUND_SIZE	Size(32.0F, 32.0F)
#define STAND_SHOOTER_CANON_TRANSLATES	T6Vec2 translate[] = {T6Vec2(0.0F, 0.0F), \
																   T6Vec2(2.0F, 0.0F)}

class StandShooter :
	public Mobs,
	public ShootObject
{
public:
	StandShooter(T6Vec3 pos);
	virtual ~StandShooter();

	virtual unsigned int getScore();

	virtual void draw();

	virtual void waitUpdate();

	virtual void activateUpdate();

	virtual void deadUpdate();

	virtual bool affect(Object* obj, DWORD key);

	virtual void setBasicProperties();

	virtual void deadEffect();

	virtual int computeShootAngle();

	virtual T6Vec3 computeShootPoint();

	virtual void update();

	virtual bool isTerminated();

private:
	int currentCanonTranslate;
};

#endif // StandShooter_h__
