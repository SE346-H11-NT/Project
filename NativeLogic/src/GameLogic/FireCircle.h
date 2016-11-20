#ifndef FireCircle_h__
#define FireCircle_h__

#include "Bullet.h"
class BulletManager;

#define BULLET_FIRE_CIRCLE_MOVE_SPEED	150
#define BULLET_SIZE_FIRE_CIRCLE	Size(16.0F, 16.0F)
#define BULLET_FIRE_CIRCLE_GYRATE_MEASURE	ANGLE_CLOCKWISE(45)

class FireCircle :
	public Bullet
{
public:
	void			shoot(int angle, T6Vec3 startPoint, int ally, float scaleX);

	void			update();
	T6Vec3		generateBullet();
	BulletType		getType();

private:
	virtual void shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX);

	FireCircle();
	virtual ~FireCircle();

	virtual void draw();

	friend BulletManager;

	int seftGyrateAngle_;
};

#endif // FireCircle_h__