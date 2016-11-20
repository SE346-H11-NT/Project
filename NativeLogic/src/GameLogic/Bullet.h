#ifndef _BULLET_H_
#define _BULLET_H_

#include "GameDefaultStructure.h"
#include "MoveObject.h"
#include "FreeSound.h"

#include "LibWrapper/T6_Include.h"

#include "GraphicAlgorithms2D\CircleEquation.h"

class BulletManager;
class Mobs;
class Character;


class Bullet : public MoveObject
{
public:
	virtual void			shoot(int angle, T6Vec3 startPoint, int ally, float scaleX)	= 0;
	virtual void			shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX) = 0;
	virtual T6Vec3		generateBullet()													= 0;

	virtual	void			update()															= 0;
	virtual void			increaseVelocity(int bonusSpeed);

	virtual BulletType		getType() = 0;

	virtual bool			isTerminated();
	virtual void			bulletEffect();
	bool					isLiving();
	void					setLivingStatus(bool newLivingStatus);
	virtual void			draw();
	void					setAlly(int newAlly);
	void					setProperties(int angle, int ally, float scaleX);
	int						getDamage();

			void			assignManager(BulletManager& manager);
			void			managerProcessing();
			int				getShootAngle();

protected:
	void					setBasicProperties();

	virtual bool			affect(Object* obj, DWORD key);

protected:
	int			shootAngle_;
	int			damage_;
	int			bulletRS_;
	BYTE		ally_;
	float		scaleX_;
	bool		rendered_;
	bool		isLiving_;

	BulletManager*	manager_;

	friend		BulletManager;
};
#endif