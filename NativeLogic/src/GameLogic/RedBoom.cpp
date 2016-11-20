#include "RedBoom.h"

RedBoom::RedBoom()
{
	Bullet::setBasicProperties();
	bulletRS_ = BulletRS::MACHINE;
	damage_ = BULLET_DAMAGE_MASSIVE;
	ally_ = ALLY_MOBS;
	activate(PROPERTIES_VISIBLE);
	gravity_ = &gravityYES;
}


RedBoom::~RedBoom()
{
}

void RedBoom::shoot(int angle, T6Vec3 startPoint, int ally, float scaleX)
{
	setProperties(angle, ally, scaleX);

	T6Vec3 velo = T6Vec3(
		RED_BOOM_DEFAULT_MOVE_SPEED * Default::cos(DEGREE_TO_RADIAN(angle)),
		RED_BOOM_DEFAULT_MOVE_SPEED * Default::sin(DEGREE_TO_RADIAN(angle)),
		0.0F);

	shoot(velo, startPoint, ally, scaleX);
}


void RedBoom::shoot(T6Vec3 velocity, T6Vec3 startPoint, int ally, float scaleX)
{
	setVelo(velocity);
	position_ = startPoint;
	*objectDefRect_ = Default::createRectFromCenter(position_, BULLET_SIZE_RED_BOOM);
	isTerminated_ = false;
	target_ = nullptr;

	managerProcessing();
}


T6Vec3 RedBoom::generateBullet()
{
	return position_;
}

void RedBoom::update()
{
	updateMoveableWithCollision(BULLET_SIZE_RED_BOOM, false, target_ == nullptr ? TOP_UNDROP : TOP_ONLY,
		Default::createRectFromCenter, UPDATE_XY);

	CollisEvent* event = CollisEvent::getFirstHappenedEvent(currentCollisEvents_);

	if (event != nullptr)
	{
		Tile *touchedTile = dynamic_cast<Tile *>(event->getTouchedObject());

		if (touchedTile->getType() >= TileType::TOP_UNDROP && !touchedTile->isWater())
		{
			isTerminated_ = true;
			bulletEffect(T6Vec3(getPosition().x, touchedTile->getRect().top, getPosition().z));
		}

		if (target_ != nullptr)
			if (getPosition().y <= target_->getPosition().y && !touchedTile->isWater())
			{
				isTerminated_ = true;
				bulletEffect(T6Vec3(getPosition().x, touchedTile->getRect().top, getPosition().z));
			}
	}
}

BulletType RedBoom::getType()
{
	return BulletType::RED_BOOM;
}

bool RedBoom::isTerminated()
{
	return (Bullet::isTerminated() || isTerminated_);
}


void RedBoom::bulletEffect()
{
	bulletEffect(position_);
}


void RedBoom::bulletEffect(T6Vec3 effectPos)
{
	if (target_ == nullptr)
		EffectManager::addExplode(effectPos);
	else
		EffectManager::addSmallExplode(effectPos);
}


void RedBoom::assignTarget(Object* target)
{
	target_ = target;
}
