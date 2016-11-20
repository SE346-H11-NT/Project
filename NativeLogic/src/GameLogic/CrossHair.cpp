#include "CrossHair.h"


CrossHair::CrossHair(T6Vec3 position, Object* target)
{
	setBasicProperties();
	position_ = position;
	Object::loadObjectResource(CROSSHAIR_RESOURCE_LINK.c_str(), 
								CROSSHAIR_NUM_OF_RESOURCE_ROW,
								CROSSHAIR_NUM_OF_RESOURCE_COLUMNS, 
								RESOURCE_MT);

	*objectDefRect_ = Default::createRectFromCenter(position_, CROSSHAIR_BOUND_SIZE);	

	assignSubPart(new BoomingCanon(position_ + CANON_1_TRANSLATE, true, 0));
	assignSubPart(new BoomingCanon(position_ + CANON_2_TRANSLATE, false, 1000));
	assignSubPart(new HiddenSniper(position_ + SNIPER_TRANSLATE, target, Size(0.55, 1.0), 12));

	staticBase_ = new T6_Texture(CROSSHAIR_STATIC_BASE_LINK.c_str());
	livingBase_ = new T6_Texture(CROSSHAIR_LIVING_BASE_LINK.c_str());
}


CrossHair::~CrossHair()
{
	SAFE_RELEASE(staticBase_);
	SAFE_RELEASE(livingBase_);
}

void CrossHair::draw()
{
	static LIGHT_COLOR;
	static int currentLight = 0;

	if (lightTimeCounter(LIGHT_TIME))
		currentLight = (currentLight + 1) % NUM_OF_LIGHT_COLOR;

	staticBase_->drawImage(position_, nullptr, SCALE_NO, CROSSHAIR_STATIC_BASE_TRANSLATE, DrawCenter::BOTTOMLEFT);
	
	if (!isDead())
	{
		livingBase_->drawImage(position_, nullptr, SCALE_NO, CROSSHAIR_LIVING_BASE_TRANSLATE, DrawCenter::BOTTOMLEFT);
		((T6_MergedTexture*) *sprites_)->draw(0, position_, DrawCenter::CENTER);
		((T6_MergedTexture*) *sprites_)->draw(1, position_, DrawCenter::CENTER, SCALE_NO, TRANSLATE_NO, ANGLE_NO, lightColor[currentLight]);
	}


	Boss::draw();
}

void CrossHair::waitUpdate()
{
	Boss::waitUpdate();
}

void CrossHair::activateUpdate()
{
	BulletManager::updateIfObjectIsShooted(this, KEY_DESTROYABLE);
	Boss::activateUpdate();
}

void CrossHair::deadUpdate()
{
	Boss::deadUpdate();
}

void CrossHair::deadEffect()
{
	Boss::deadEffect();
	srand((unsigned int)time(nullptr));
	FOR(10)
	{
		T6Vec3 effectPos;
		effectPos.x = position_.x + CROSSHAIR_LIVING_BASE_TRANSLATE.x + (rand() % (int)livingBase_->getFrameSize().width);
		effectPos.y = position_.y + CROSSHAIR_LIVING_BASE_TRANSLATE.y + (rand() % (int)livingBase_->getFrameSize().height);
		effectPos.z = DEFAULT_DEPTH;

		EffectManager::addExplode(
			effectPos,
			i * DEFAULT_FRAME_TIME);
	}
}


void CrossHair::setBasicProperties()
{
	Boss::setBasicProperties();
	heathPoints_ = CROSSHAIR_HEALTH_POINTS;
	Object::activate(PROPERTIES_VISIBLE);
	Object::deactivate(PROPERTIES_EVATION);
}


bool CrossHair::affect(Object* obj, DWORD key)
{
	if (CHECK_KEY(key, KEY_MOVEABLE))
	{
		MoveObject *moveObject = dynamic_cast<MoveObject *>(obj);

		if (NULL != moveObject)
		{
			double time = 0;
			Direction direct = Direction::NONE;

			if (isTouchable())
				time = Collision::checkCollision(moveObject, this, &direct);

			if (direct != Direction::NONE) { // If the object touched this tile.
				if (time <= Timer::getRoundTime() && time >= 0) // If this collision happened sooner than current result, replace it, then.
					{
					if (time == 0)
					{
						switch (direct)
						{
						case UP:	if (moveObject->getRect().bottom < this->getRect().top)	return false; break;
						case DOWN:	if (moveObject->getRect().top > this->getRect().bottom)	return false; break;
						case LEFT:	if (moveObject->getRect().right > this->getRect().left)	return false; break;
						case RIGHT:	if (moveObject->getRect().left < this->getRect().right)	return false; break;
						default: break;
						}
					}

					moveObject->pushCollisEvent(new CollisEvent(this, direct, time));
					}
			}
		}
	}

	return false;
}


bool CrossHair::lightTimeCounter(DWORD timeCap)
{
	static DWORD timer = 0;
	timer += Timer::getRoundTime();

	if (timer >= timeCap)
	{
		timer = 0;
		return true;
	}

	return false;
}
