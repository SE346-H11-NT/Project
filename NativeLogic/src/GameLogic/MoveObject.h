#ifndef __MOVE_OBJECT_H__
#define __MOVE_OBJECT_H__

#include <vector>

#include "Object.h"
#include "GameDefaultConstant.h"
#include "Collision.h"

class Map;

union Velocity {

	struct {
		float x;
		float y;
		float z;
	};

	float direct;


	Velocity()
	{
		ZeroMemory(this, sizeof(Velocity));
	}


	Velocity(float x, float y, float z = 0.0F)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}


	Velocity(float direct)
	{
		ZeroMemory(this, sizeof(Velocity));
		this->direct = direct;
	}


	Velocity(T6Vec3 velo)
	{
		this->x = velo.x;
		this->y = velo.y;
		this->z = velo.z;
	}


	Velocity operator * (float d)
	{
		return Velocity(x * d, y * d, z * d);
	}


	Velocity operator = (T6Vec3 v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}


	operator T6Vec3()
	{
		return T6Vec3(x, y, z);
	}
};


class MoveObject : virtual public Object
{
public:
	virtual void					update(double moveTime = Timer::getRoundTime(),
											T6Rect(*createT6RectFunction)(T6Vec3, Size) = Default::createRectFromCenter,
											Size boundSize = Size(1.0, 1.0),
											int updateDirect = UPDATE_XY,
											bool isUpdateScale = true);

	virtual void update();

	virtual void					draw() = 0;
	virtual bool					isTerminated();
	virtual							~MoveObject(){};
	virtual	vector<CollisEvent*>	updateMoveableWithCollision(
		Size boundSize, 
		bool isSwimCollis = true, 
		int collisLevel = 0, 
		T6Rect(*createRectFunction)(T6Vec3, Size) = Default::createRectFromBottomCenter,
		DWORD absoluteUpdate = UPDATE_NONE);

	T6Vec3* getVelo();
	void setVelo(T6Vec3 newVelo);
	void activateFallThrough();
	void deactivateFallThrough();
	vector<CollisEvent*> getCollisEvent();
	void pushCollisEvent(CollisEvent* newCollis);

	virtual void commandJump();
	virtual bool  affect(Object* obj, DWORD key) = 0;

protected:
	static	void	gravityYES(MoveObject* object);
	static	void	gravityNO(MoveObject* object);
	virtual void	setBasicProperties();

protected:
	T6Vec3 velocity_;
	bool		fallThrough_;
	vector<Object*> ignoredCollisObject_;
	void		(*gravity_)(MoveObject*);


	vector<CollisEvent*> currentCollisEvents_;

private:
	void detectCurrentCollisEvent(bool isWaterCollis, int collisLevel);
};

#endif