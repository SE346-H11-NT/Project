#ifndef FallingStone_h__
#define FallingStone_h__

#include "Mobs.h"
#include "MoveObject.h"

#define SCORE_FALLING_STONE				100
#define FALLING_STONE_RESOURCE_LINK		(tstring(_T("Resource//Mobs//FallingStone")) + EXTENSION_PICTURE)
#define FALLING_STONE_RESOURCE_ROWS		1
#define FALLING_STONE_RESOURCE_COLUMNS	1
#define FALLING_STONE_HEALTH_POINTS		50
#define FALLING_STONE_BOUND_SIZE		Size(24.0, 24.0)
#define FALLING_STONE_ROLL_TIME			3000
#define FALLING_STONE_RELOAD_TIME		5000	
#define FALLING_STONE_JUMP_VELO			(SPEED_XY(0.0F, JUMP_SPEED / 2.0))
#define FALLING_STONE_FRAME_TIME		(DEFAULT_FRAME_TIME)
#define SCALE_CASE						T6Vec2 scale[] = {SCALE_NO, SCALE_FLIP_Y, SCALE_FLIP_XY, SCALE_FLIP_X}
#define NUM_OF_SCALE_CASE				4
#define ROLLING_TRANSLATE				T6Vec2(1.0F, 0.0F)

enum FallingStoneState
{	
	FALLING_STONE_ROOL = 0,
	FALLING_STONE_FALL
};

class FallingStone :
	public Mobs,
	public MoveObject
{
public:
	FallingStone(T6Vec3 position);
	virtual ~FallingStone();

	virtual unsigned int getScore();

	virtual void draw();

	virtual void waitUpdate();

	virtual void activateUpdate();

	virtual void deadUpdate();

	virtual void setBasicProperties();

	virtual void deadEffect();

	virtual bool isDead();

	virtual void update();

	virtual bool affect(Object* obj, DWORD key);

	virtual bool isTerminated();

	virtual void commandJump();

	virtual void reset();

private:
	DWORD timeCounter_;
	T6Vec3 respawPos_;
	static T6Vec2 translate_;
	int currentRollingAngle_;
};

#endif // FallingStone_h__
