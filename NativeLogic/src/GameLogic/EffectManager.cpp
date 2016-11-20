#include "EffectManager.h"


EffectManager* EffectManager::instance_ = nullptr;


EffectManager::EffectManager()
{
}


EffectManager::~EffectManager()
{
}


void EffectManager::add(Effect* newEffect)
{
	getInstance().livingEffects_.push_back(newEffect);
}


void EffectManager::draw()
{
	vector<Effect*>* effects = &getInstance().livingEffects_;

	FOR(effects->size())
	{
		if (effects->at(i)->draw())
		{
			SAFE_RELEASE(effects->at(i));
			effects->erase(effects->begin() + i);
			i--;
		}
	}
}


EffectManager& EffectManager::getInstance()
{
	if (instance_ == nullptr)
		instance_ = new EffectManager();

	return *instance_;
}


double EffectManager::getExplodeTime()
{
	return EFFECT_EXPLODE_FRAME_TIME;
}




void EffectManager::addExplode		(T6Vec3 position, DWORD delayTime /*= 0*/)
{
	Effect* newEffect = new Effect(EFFECT_EXPLODE_LINK.c_str(), EFFECT_EXPLODE_COLUMNS, EFFECT_EXPLODE_ROWS, position, delayTime);
	newEffect->setFrameTime(EFFECT_EXPLODE_FRAME_TIME);
	EffectManager::add(newEffect);
}
void EffectManager::addBulletExplode(T6Vec3 position, DWORD delayTime /*= 0*/)
{
	Effect* newEffect = new Effect(EFFECT_EXPLODE_BULLET_LINK.c_str(), EFFECT_EXPLODE_BULLET_COLUMNS, EFFECT_EXPLODE_BULLET_ROWS, position, delayTime);
	newEffect->setFrameTime(EFFECT_EXPLODE_BULLET_FRAME_TIME);
	EffectManager::add(newEffect);
}
void EffectManager::addSmallExplode	(T6Vec3 position, DWORD delayTime /*= 0*/)
{
	Effect* newEffect = new Effect(EFFECT_EXPLODE_SMALL_LINK.c_str(), EFFECT_EXPLODE_SMALL_COLUMNS, EFFECT_EXPLODE_SMALL_ROWS, position, delayTime);
	newEffect->setFrameTime(EFFECT_EXPLODE_SMALL_FRAME_TIME);
	EffectManager::add(newEffect);
}
void EffectManager::addWaterFlow	(T6Vec3 position, DWORD delayTime /*= 0*/)
{
	Effect* newEffect = new Effect(EFFECT_WATER_FLOW_LINK.c_str(), EFFECT_WATER_FLOW_COLUMNS, EFFECT_WATER_FLOW_ROWS, position, delayTime);
	newEffect->setFrameTime(EFFECT_WATER_FLOW_FRAME_TIME);
	EffectManager::add(newEffect);
}