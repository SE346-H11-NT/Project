#include "FireCircle.h"
#include "BulletManager.h"

void FireCircle::shoot(int angle, T6Vec3 startPoint, int ally, float scaleX)
{
	setProperties(angle, ally, scaleX);

	shoot(T6Vec3(BULLET_FIRE_CIRCLE_MOVE_SPEED * Default::cos(DEGREE_TO_RADIAN(angle)),
		BULLET_FIRE_CIRCLE_MOVE_SPEED * Default::sin(DEGREE_TO_RADIAN(angle)),
		0.0F),
		startPoint,
		ally,
		scaleX);
}

void FireCircle::shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX)
{
	seftGyrateAngle_ = 0;

	setVelo(velocity);

	position_ = startPoint;

	*objectDefRect_ = Default::createRectFromCenter(position_, BULLET_SIZE_FIRE_CIRCLE);

	managerProcessing();
}

void FireCircle::update()
{
	MoveObject::update(Timer::getRoundTime(), Default::createRectFromCenter, BULLET_SIZE_FIRE_CIRCLE, UPDATE_XY);
	seftGyrateAngle_ += BULLET_FIRE_CIRCLE_GYRATE_MEASURE;
	generateBullet();
}

T6Vec3 FireCircle::generateBullet()
{
	return Object::position_;
}

BulletType FireCircle::getType()
{
	return BulletType::FIRE_CIRCLE;
}

FireCircle::FireCircle()
{
	Bullet::setBasicProperties();
	bulletRS_ = BulletRS::ENERGY_FIRE;
	damage_ = BULLET_DAMAGE_MASSIVE;
}

FireCircle::~FireCircle()
{

}

void FireCircle::draw()
{
	if (rendered_)
		(*sprites_)->render(Timer::getRoundTime(), position_, seftGyrateAngle_, SCALE_NO,
		TRANSLATE_NO, DrawCenter::CENTER, COLOR_NO, bulletRS_, bulletRS_);
}
