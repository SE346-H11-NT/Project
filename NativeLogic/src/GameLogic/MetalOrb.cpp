#include "MetalOrb.h"


MetalOrb::MetalOrb(T6Vec3 position)
{
	setBasicProperties();
	setPos(position);
	Object::loadObjectResource(METAL_ORB_RESOURCE_LINK.c_str(), METAL_ORB_RESOURCE_ROWS, METAL_ORB_RESOURCE_COLUMNS, RESOURCE_MS);
}


MetalOrb::~MetalOrb()
{
}

unsigned int MetalOrb::getScore()
{
	return 0;
}

void MetalOrb::waitUpdate()
{
	activate();
}

void MetalOrb::activateUpdate()
{
	BulletManager::updateIfObjectIsShooted(this, KEY_NO);
}

void MetalOrb::deadUpdate()
{
}

bool MetalOrb::affect(Object* obj, DWORD key)
{
	return false;
}

void MetalOrb::setBasicProperties()
{
	Mobs::setBasicProperties();
	Object::activate(PROPERTIES_IMMORTAL);
}

void MetalOrb::deadEffect()
{
	EffectManager::addExplode(position_);
}


void MetalOrb::setPos(T6Vec3 newPos)
{
	position_ = newPos;
	*objectDefRect_ = Default::createRectFromCenter(position_, METAL_ORB_BOUND_SIZE);
}

void MetalOrb::draw()
{
	(*sprites_)->render(Timer::getRoundTime(), position_, ANGLE_NO, SCALE_NO, TRANSLATE_NO, DrawCenter::CENTER);
}
