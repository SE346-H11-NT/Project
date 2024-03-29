#ifndef DiveShooter_h__
#define DiveShooter_h__

#include "Mobs.h"
#include "ShootObject.h"

#define DIVE_SHOOTER_RESOURCE_LINK (tstring(_T("Resource//Mobs//DiveShooter")) + EXTENSION_PICTURE)
#define DIVE_SHOOTER_RESOURCE_ROWS	1
#define DIVE_SHOOTER_RESOURCE_COLUMNS	2
#define DIVE_SHOOTER_RELOAD_TIME	2000
#define DIVE_SHOOTER_SHOOT_TIME		1000
#define DIVE_SHOOTER_UPDATE_DISTANCE	20
#define DIVE_SHOOTER_BOUND_SIZE		Size(16.0, 16.0)
#define DIVE_SHOOTER_ACTIVATE_DISTANCE	(RESOLUTION_HEIGHT / 2.0)
#define DIVE_SHOOTER_SHOOTPOINT_DISTANCE_FROM_POSITION	T6Vec3(4.0F, 30.0F, 0.0F)
#define DIVE_SHOOTER_GOOD_DISTANCE_TO_TARGET_Y	20
#define DIVE_SHOOTER_FRAME_TIME (DEFAULT_FRAME_TIME * 2)

#define SCORE_DIVE_SHOOTER		500

enum DiveShooterState
{
	DIVE_SHOOTER_DIVING = 0,
	DIVE_SHOOTER_SHOOT
};

class DiveShooter :
	public Mobs,
	public ShootObject
{
public:
	DiveShooter(T6Vec3 position, Object* target);
	virtual ~DiveShooter();

	virtual unsigned int getScore();

	virtual void draw();

	virtual void waitUpdate();

	virtual void activateUpdate();

	virtual void deadUpdate();

	virtual bool affect(Object* obj, DWORD key);

	virtual void setBasicProperties();

	virtual void deadEffect();

	virtual bool isDead();

	virtual void update();

	virtual bool isTerminated();

	virtual int computeShootAngle();

	virtual T6Vec3 computeShootPoint();

private:
	void computeTranslate();

private:
	T6Vec2 translate_;
	Object* target_;
	DWORD timer_;
	DWORD frameTime_;
};

#endif // DiveShooter_h__
