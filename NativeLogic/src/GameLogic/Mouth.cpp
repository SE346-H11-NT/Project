#include "Mouth.h"

Mouth::Mouth(T6Vec3 pos, Object* player)
{
	setBasicProperties();
	position_ = pos + MOUTH_MOUTH_TRANSLATE;
	basePos_ = pos;
	target_ = player;
	*objectDefRect_ = Default::createRectFromDrawCenter(getPosition(), MOUTH_BOUND_SIZE, DrawCenter::TOPCENTER);
	Object::loadObjectResource(MOUTH_RESOURCE_MOUTH.c_str(), MOUTH_RESOURCE_MOUTH_ROWS, MOUTH_RESOURCE_MOUTH_COLUMNS, RESOURCE_MS);

	assignSubPart(new Tentacle(getPosition() + MOUTH_TENTACLE_L_POS_FIX, MOUTH_TENTACLE_L_ANGLE, player));
	assignSubPart(new Tentacle(getPosition() + MOUTH_TENTACLE_R_POS_FIX, MOUTH_TENTACLE_R_ANGLE, player));
}


Mouth::~Mouth()
{
	SAFE_RELEASE(staticBase_);
	SAFE_RELEASE(livingBase_);
	SAFE_RELEASE(head_);
}

unsigned int Mouth::getScore()
{
	return Boss::getScore();
}

void Mouth::draw()
{
	static int timer = 0;

	staticBase_->drawImage(basePos_, nullptr, SCALE_NO, MOUTH_STATIC_BASE_TRANSLATE, DrawCenter::BOTTOMCENTER, ANGLE_NO, opacity_);

	if (!isDead())
	{
		timer += Timer::getRoundTime();
		if (timer >= DEFAULT_FRAME_TIME)
		{
			currentEyeColorIndex_ = (currentEyeColorIndex_ + 1) % MOUTH_EYES_NUM_OF_COLOS;
			timer = 0;
		}

		static MOUTH_EYES_COLORS;
		livingBase_->drawImage(basePos_, nullptr, SCALE_NO, MOUTH_LIVING_BASE_TRANSLATE, DrawCenter::BOTTOMCENTER, ANGLE_NO, opacity_);
		head_->draw(0, getPosition(), DrawCenter::TOPCENTER, SCALE_NO, MOUTH_HEAD_TRANSLATE, ANGLE_NO, opacity_);
		head_->draw(1, getPosition(), DrawCenter::TOPCENTER, SCALE_NO, MOUTH_HEAD_TRANSLATE, ANGLE_NO, eyeColors[currentEyeColorIndex_] & opacity_);

		switch (status_)
		{
		case MOUTH_CLOSE:
			sprites_[0]->render(Timer::getRoundTime(), getPosition(),
				ANGLE_NO, SCALE_NO, TRANSLATE_NO, DrawCenter::TOPCENTER, opacity_, 0, 0);
			break;

		case MOUTH_CLOSING:
			sprites_[0]->render(Timer::getRoundTime(), getPosition(),
				ANGLE_NO, SCALE_NO, TRANSLATE_NO, DrawCenter::TOPCENTER, opacity_, MOUTH_FRAME_NUM - 1, 0);
			break;

		case MOUTH_OPENING:
			sprites_[0]->render(Timer::getRoundTime(), getPosition(),
				ANGLE_NO, SCALE_NO, TRANSLATE_NO, DrawCenter::TOPCENTER, opacity_, 0, -1);
			break;

		case MOUTH_OPEN:
			sprites_[0]->render(Timer::getRoundTime(), getPosition(),
				ANGLE_NO, SCALE_NO, TRANSLATE_NO, DrawCenter::TOPCENTER, opacity_, MOUTH_FRAME_NUM - 1, MOUTH_FRAME_NUM - 1);
			break;
		default:
			break;
		}
	}

	Boss::draw();
}

void Mouth::waitUpdate()
{
	Boss::waitUpdate();
}

void Mouth::activateUpdate()
{
	Boss::activateUpdate();
	timeCounter_ += Timer::getRoundTime();
	BulletManager::updateIfObjectIsShooted(this, KEY_DESTROYABLE);

	switch (status_)
	{
	case MOUTH_CLOSE:
		if (timeCounter_ >= MOUTH_CLOSE_TIME)
		{
			timeCounter_ = 0;
			status_ = MOUTH_OPENING;
		}
		break;

	case MOUTH_CLOSING:
		if (sprites_[0]->isComplete())
		{
			timeCounter_ = 0;
			status_ = MOUTH_CLOSE;
			Object::activate(PROPERTIES_EVATION);
		}
		break;

	case MOUTH_OPENING:
		if (sprites_[0]->isComplete())
		{
			timeCounter_ = 0;
			status_ = MOUTH_OPEN;
			Object::deactivate(PROPERTIES_EVATION);
		}
		break;

	case MOUTH_OPEN:
		if (timeCounter_ <= Timer::getRoundTime())
		{
			FOR(MOUTH_NUM_OF_SHOOT_ANGLE)
				instanceShoot();
		}
		
		if (timeCounter_ >= MOUTH_OPEN_TIME)
		{
			timeCounter_ = 0;
			status_ = MOUTH_CLOSING;
		}
		break;
	default:
		break;
	}
}

void Mouth::deadEffect()
{
	Boss::deadEffect();
	srand((unsigned int)time(nullptr));
	FOR(10)
	{
		T6Vec3 effectPos;
		effectPos.x = position_.x + MOUTH_LIVING_BASE_TRANSLATE.x + (rand() % (int)livingBase_->getFrameSize().width);
		effectPos.y = position_.y + MOUTH_LIVING_BASE_TRANSLATE.y + (rand() % (int)livingBase_->getFrameSize().height);
		effectPos.z = DEFAULT_DEPTH;

		EffectManager::addExplode(
			effectPos,
			i * DEFAULT_FRAME_TIME);
	}
}

void Mouth::setBasicProperties()
{
	Boss::setBasicProperties();
	ShootObject::setBasicProperties();
	Object::activate(PROPERTIES_EVATION);

	heathPoints_ = MOUTH_LIFE_POINTS;

	currentBullet_ = BulletType::FIRE_CIRCLE;

	staticBase_ = new T6_Texture(MOUTH_STATIC_BASE.c_str());
	livingBase_ = new T6_Texture(MOUTH_LIVING_BASE.c_str());
	head_ = new T6_MergedTexture(MOUTH_RESOURCE_HEAD.c_str(), MOUTH_RESOURCE_HEAD_COLUMNS, MOUTH_RESOURCE_HEAD_ROWS);
	opacity_ = 0x00ffffff;
}

void Mouth::update()
{
	Boss::update();
}

int Mouth::computeShootAngle()
{
	static int angleIndex = 0;

	static MOUTH_SHOOT_ANGLES;

	angleIndex = (angleIndex + 1) % MOUTH_NUM_OF_SHOOT_ANGLE;
	return shootAngles[angleIndex];
}

T6Vec3 Mouth::computeShootPoint()
{
	return getPosition();
}

bool Mouth::affect(Object* obj, DWORD key)
{
	return false;
}

bool Mouth::isTerminated()
{
	return Boss::isTerminated();
}

void Mouth::activate()
{
	DWORD fade = (DWORD)TRUE_SPEED(MOUTH_FADE_SPEED, Timer::getRoundTime());
	
	if ((opacity_ >> 24) > (255 - fade))
	{
		opacity_ = 0xffffffff;
		Boss::activate();
	}
	else
	{
		opacity_ += (fade << 24);
	}
}