#ifndef RedSpreadBoom_h__
#define RedSpreadBoom_h__

#include "Bullet.h"

#define RED_SPREAD_BLOW_DISTANCE	100.0F
#define RED_SPREAD_BOUND_SIZE	Size(3.0, 3.0)
#define RED_SPREAD_MOVE_SPEED	300.0F
#define RED_SPREAD_BLOW_TIME	((RED_SPREAD_BLOW_DISTANCE / RED_SPREAD_MOVE_SPEED) * 1000)
#define RED_SPREAD_NUM_OF_BOOM_GENERATED	3
#define RED_SPREAD_BOOM_VELO_Y	120.0F
#define RED_SPREAD_BOOM_VELO	T6Vec3	generatedBoomVelo[] = {SPEED_XY(-60, RED_SPREAD_BOOM_VELO_Y), SPEED_XY(0, RED_SPREAD_BOOM_VELO_Y), SPEED_XY(60, RED_SPREAD_BOOM_VELO_Y)}


class RedSpreadBoom :
	public Bullet
{
public:
	RedSpreadBoom();
	virtual ~RedSpreadBoom();

	virtual void shoot(int angle, T6Vec3 startPoint, int ally, float scaleX);

	virtual T6Vec3 generateBullet();

	virtual void update();

	virtual BulletType getType();

	virtual bool isTerminated();

	virtual void bulletEffect();

	virtual bool affect(Object* obj, DWORD key);

			void assignTarget(Object* target);

private:
	virtual void shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX);

private:
	DWORD timeCounter_;
	Object* target_;

};

#endif // RedSpreadBoom_h__