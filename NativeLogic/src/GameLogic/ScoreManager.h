#ifndef ScoreManager_h__
#define ScoreManager_h__

#define EXTRA_LIFE_SCORE_CAP	10000
#define DEFAULT_HIGH_SCORE		20000

class Character;

class ScoreManager
{
public:
	static bool increase(int score);
	static unsigned long getScore();
	static unsigned long getHighScore();
	static void initialize(Character* player);
	static void reset();

private:
	static ScoreManager* get();
	ScoreManager();
	~ScoreManager();

	static ScoreManager* instance_;

private:
	unsigned long score_;
	unsigned long highScore_;
	Character* player_;
};

#endif // ScoreManager_h__
