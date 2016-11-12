#ifndef __GAME_MAIN__
#define __GAME_MAIN__

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
};

#endif // !__GAME_MAIN__
