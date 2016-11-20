#include "Fire.h"


Fire::Fire(T6Vec3 position, T6Vec3 velocity, T6Rect moveRange)
{
	setBasicProperties();
	position_ = position;
	setVelo(velocity);
	moveRange_ = moveRange;
	Object::loadObjectResource(FIRE_RESOURCE_LINK.c_str(), FIRE_RESOURCE_ROWS, FIRE_RESOURCE_COLUMNS, RESOURCE_MS);
	*objectDefRect_ = Default::createRectFromBottomCenter(position_, FIRE_BOUND_SIZE);
}


Fire::~Fire()
{
}

void Fire::draw()
{
	(*sprites_)->render(Timer::getRoundTime(), position_, ANGLE_NO, scale_, TRANSLATE_NO, DrawCenter::BOTTOMCENTER);
}

void Fire::waitUpdate()
{
	if (Default::checkIfBounded(objectDefRect_, &Camera::getViewPort()))
	{
		activate();
	}
}

void Fire::activateUpdate()
{
	frameTime_ += Timer::getRoundTime();

	if (frameTime_ >= FIRE_FRAME_TIME)
	{
		frameTime_ = 0;
		scale_.x = -scale_.x;
	}

	MoveObject::update(Timer::getRoundTime(), Default::createRectFromBottomCenter, FIRE_BOUND_SIZE, UPDATE_X, false);

	if (objectDefRect_->left < moveRange_.left)
		setVelo(T6Vec3(fabs(getVelo()->x), getVelo()->y, getVelo()->z));
	else if (objectDefRect_->right > moveRange_.right)
		setVelo(T6Vec3(-fabs(getVelo()->x), getVelo()->y, getVelo()->z));
}

void Fire::deadUpdate()
{
}

bool Fire::affect(Object* obj, DWORD key)
{
	return Mobs::affect(obj, key);
}

void Fire::setBasicProperties()
{
	MoveObject::setBasicProperties();
	Mobs::setBasicProperties();
}

void Fire::update()
{
	Mobs::update();
}

bool Fire::isTerminated()
{
	return (objectDefRect_->top < Camera::getViewPort().bottom);
}

unsigned int Fire::getScore()
{
	return 0;
}

void Fire::deadEffect()
{
}