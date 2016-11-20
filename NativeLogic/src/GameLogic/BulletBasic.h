#ifndef _BULLET_BASIC_
#define _BULLET_BASIC_

#include "Bullet.h"

class BulletBasic : public Bullet
{	
public:
	void			shoot(int angle, T6Vec3 startPoint, int ally, float scaleX);


	void			update();
	T6Vec3		generateBullet();
	BulletType		getType();

private:
	virtual void shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX);

	BulletBasic(int ally);
	~BulletBasic();
	friend BulletManager;
	BulletType type_;
};
#endif