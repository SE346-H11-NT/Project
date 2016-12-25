#ifndef _BULLET_LASER_
#define _BULLET_LASER_

#define GENERATE_TIME	30

#include "Bullet.h"

#define BULLET_L_MOVE_SPEED		300
#define BULLET_L_LATE_START		(-12)
#define BULLET_L_ACTIVATE_TIME	DWORD activateTime[] = {0, 0, 15, 30}
#define BULLET_L_SOUND			_T("Resource//SoundTrack//L")

class BulletLaser : public Bullet
{
public:
	void			shoot(int angle, T6Vec3 startPoint, int ally, float scaleX);

	virtual void shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX);

	void			update();
	T6Vec3		generateBullet();
	BulletType		getType();

	virtual void draw();

private:
	BulletLaser();
	~BulletLaser();

	void	removeBulletLaserInManager();
	void	singleBulletFire(int angle, T6Vec3 startPoint, int ally, float scaleX);
	bool	checkIfActivated();

	friend BulletManager;

private:
	bool isGenerated_;
	float movedDistance_;
	static int laserCounter;
};
#endif