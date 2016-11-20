#ifndef RedBoom_h__
#define RedBoom_h__

#include "Bullet.h"
#include "EffectManager.h"
#include "Tile.h"

#define RED_BOOM_DEFAULT_MOVE_SPEED	300.0F

class RedBoom :
	public Bullet
{
public:
	RedBoom();
	virtual ~RedBoom();

	virtual void shoot(int angle, T6Vec3 startPoint, int ally, float scaleX);

	virtual void shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX);

	virtual T6Vec3 generateBullet();

	virtual void update();

	virtual BulletType getType();
			
			void assignTarget(Object* target);

	virtual bool isTerminated();

	virtual void bulletEffect();

	virtual void bulletEffect(T6Vec3 effectPos);

private:
	Object* target_;
	bool isTerminated_;
};

#endif // RedBoom_h__
