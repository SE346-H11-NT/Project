#ifndef __BULLET_FIRE_H__
#define __BULLET_FIRE_H__

#include "Bullet.h"

class BulletFire : public Bullet
{
public:
	void			shoot(int angle, T6Vec3 startPoint, int ally, float scaleX);

	void			update();
	T6Vec3		generateBullet();
	BulletType		getType();

	virtual void draw();


private:
	virtual void shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX);

	BulletFire();
	~BulletFire();


	friend BulletManager;

private:
	int				selfRotateDegree_;
	T6Vec3		centerPos_;
};

#endif