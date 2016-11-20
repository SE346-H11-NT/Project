#ifndef __BULLET_SPREAD_H__
#define __BULLET_SPREAD_H__

#include "Bullet.h"

#define BULLET_S_MOVE_SPEED		200
#define BULLET_S_SPREAD_LEVEL	5
#define BULLET_S_SPREAD_ANGLE	int spreadAngle[] = {0, -11, 9, -21, 19}
#define BULLET_S_SOUND			_T("Resource//SoundTrack//S.wav")

class BulletSpread : public Bullet
{
public:
	void			shoot(int angle, T6Vec3 startPoint, int ally, float scaleX);


	void			update();
	T6Vec3		generateBullet();
	BulletType		getType();

private:
	virtual void shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX);

	BulletSpread();
	~BulletSpread();

	virtual void draw();

	virtual void increaseVelocity(int bonusSpeed);

	friend BulletManager;

private:
	int flydistance_;
	vector<Bullet*> instances_;
};

#endif