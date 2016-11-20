#include "ScoreManager.h"
#include "Character.h"

ScoreManager::ScoreManager()
{
	score_ = 0;
	highScore_ = DEFAULT_HIGH_SCORE;
}

ScoreManager::~ScoreManager()
{

}

bool ScoreManager::increase(int score)
{
	get()->score_ += score;

	if ((get()->score_ % EXTRA_LIFE_SCORE_CAP) < score)
	{
		get()->player_->bonusLife();
		return true;
	}

	return false;
}

ScoreManager* ScoreManager::get()
{
	if (instance_ == nullptr)
	{
		instance_ = new ScoreManager();
	}

	return instance_;
}

unsigned long ScoreManager::getScore()
{
	return get()->score_;
}

unsigned long ScoreManager::getHighScore()
{
	if (get()->highScore_ < get()->score_)
	{
		get()->highScore_ = get()->score_;
	}

	return get()->highScore_;
}

void ScoreManager::initialize(Character* player)
{
	get()->player_ = player;
}

void ScoreManager::reset()
{
	get()->score_ = 0;
}

ScoreManager* ScoreManager::instance_;
