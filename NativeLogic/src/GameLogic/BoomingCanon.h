#ifndef BoomingCanon_h__
#define BoomingCanon_h__

#include "Mobs.h"
#include "ShootObject.h"
#include "BulletManager.h"

#define SCORE_BOOMING_CANON				500
#define BOOMING_CANON_RESOURCE_LINK		(tstring(_T("Resource//Bosses//TheWall//BoomingCanon")) + EXTENSION_PICTURE)
#define BOOMING_CANON_RESOURCE_COLUMNS	2
#define BOOMING_CANON_RESOURCE_ROWS		1
#define BOOMING_CANON_HEALTH_POINTS		20
#define BOOMING_CANON_BOUND_SIZE		Size(15.0, 12.0)
#define BOOMING_CANON_GUARD_TRANSLATE	T6Vec2(10.0F, 0.0F)
#define BOOMING_CANON_SHOOT_STATE_TIME	(DEFAULT_FRAME_TIME * 2)


enum BoomingCanonState
{
	BCS_RELOAD = 0,
	BCS_READY_TO_SHOOT,
	BCS_SHOOT,
	NUM_OF_BCS_STATE
};

class BoomingCanon :
	public Mobs,
	public ShootObject
{
public:
	BoomingCanon(T6Vec3 position, bool drawGuards, DWORD countedTime);
	virtual ~BoomingCanon();

	virtual unsigned int getScore();

	virtual void draw();

	virtual void waitUpdate();

	virtual void activateUpdate();

	virtual void deadUpdate();

	virtual void deadEffect();

	virtual void setBasicProperties();

	virtual int computeShootAngle();

	virtual T6Vec3 computeShootPoint();

	virtual void update();

	virtual bool affect(Object* obj, DWORD key);

	virtual bool isTerminated();

			bool stateProcess();

private:
	Bullet*	shootedBullet_;
	bool	isDrawGuards_;
	DWORD	timeCounter_;

private:
	T6Vec3 computeBulletLauchVelo();
};

#endif // BoomingCanon_h__
