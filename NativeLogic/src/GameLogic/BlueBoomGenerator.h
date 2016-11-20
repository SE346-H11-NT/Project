#ifndef BlueBoomGenerator_h__
#define BlueBoomGenerator_h__

#include "Object.h"
#include "BlueBoom.h"
#include "Map.h"

#define BB_GENERATOR_DELAY	2000

class BlueBoomGenerator :
	public Object
{
public:
	BlueBoomGenerator(T6Vec3 pos);
	virtual ~BlueBoomGenerator();

	virtual void setBasicProperties();

	virtual void update();

	virtual void draw();

	virtual bool affect(Object* obj, DWORD key);

	virtual bool isTerminated();

private:
	DWORD timeCounter_;
};

#endif // BlueBoomGenerator_h__
