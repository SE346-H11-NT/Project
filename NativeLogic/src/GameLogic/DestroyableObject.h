#ifndef DestroyableObject_h__
#define DestroyableObject_h__

#include "Object.h"
#include "FreeSound.h"

#define DAMAGE_SOUND	_T("Resource//Soundtrack//Damaged.wav")

class DestroyableObject : virtual public Object
{
public:
	~DestroyableObject();

	virtual bool isDead();
	virtual void damaged(unsigned int damage, DWORD deadCounter = 0);
	void dead(DWORD deadCounter);

	virtual void update();

	virtual void setBasicProperties();

	virtual void draw() = 0;

	void checkIfShooted();

	virtual bool isTerminated();

protected:
	unsigned int heathPoints_;

private:
	virtual void deadEffect() = 0;


private:
	DWORD deadCounter_;
};

#endif // DestroyableObject_h__
