#ifndef __SHOOT_OBJECT_H__
#define __SHOOT_OBJECT_H__

#include "Object.h"
#include "GameDefaultConstant.h"
#include "GameDefaultStructure.h"

#include "GraphicAlgorithms2D\T6Math.h"
#include "GraphicAlgorithms2D\MathDefaultConstant.h"

class Bullet;
class BulletManager;

class ShootObject : public virtual Object
{
public:
			void		draw()				= 0;
	virtual int			computeShootAngle() = 0;
	virtual T6Vec3 computeShootPoint() = 0;
	virtual bool		isTerminated()		= 0;
	virtual				~ShootObject(){};

	virtual void	update();
	virtual Bullet*	shoot(T6Vec3 velocity = SPEED_NO);
	Bullet* instanceShoot(T6Vec3 velocity = SPEED_NO);
	virtual void	setBasicProperties();
			void	changeBullet(BulletType newBullet);
			int		getShootDirection(T6Vec3* target);

			virtual bool  affect(Object* obj, DWORD key);

protected:
	BulletType		currentBullet_;
	double			lastShootTime_;
};

#include "Bullet.h"
#include "BulletManager.h"

#endif