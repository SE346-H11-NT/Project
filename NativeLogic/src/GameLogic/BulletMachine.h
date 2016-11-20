#ifndef _BULLET_MACHINE_
#define _BULLET_MACHINE_

#include "Bullet.h"

#define BULLET_M_SOUND			_T("Resource//SoundTrack//M.wav")

class BulletMachine : public Bullet
{
public:
	void			shoot(int angle, T6Vec3 startPoint, int ally, float scaleX);

	void			update();
	T6Vec3		generateBullet();
	BulletType		getType();

private:
	virtual void shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX);

	BulletMachine();
	BulletMachine(int ally);
	~BulletMachine();
	friend BulletManager;
};
#endif