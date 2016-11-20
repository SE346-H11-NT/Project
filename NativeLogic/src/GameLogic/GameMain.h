#ifndef __GAME_MAIN__
#define __GAME_MAIN__

#include "T6_Include.h"

class GameMain
{
public:
	static GameMain* getInstance();
	static void initialize();
	static void release();

	void update(double deltaTime);
	void draw();

private:
	GameMain();
	~GameMain();

private:
	static GameMain* m_instance;
	T6_Keyboard*	keyboard_;
};

#endif // !__GAME_MAIN__
