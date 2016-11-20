#include "Object.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

Object::~Object()
{
	SAFE_RELEASE(sprites_);
	SAFE_RELEASE(objectDefRect_);
}


void Object::setBasicProperties()
{
	currentImmortalStatus_ = Object::propertiesNo;
	currentShootableStatus_ = Object::propertiesYes;
	currentTouchableStatus_ = Object::propertiesYes;
	try
	{
		SAFE_RELEASE(objectDefRect_);
	}
	catch (exception* e){}

	objectDefRect_ = new T6Rect();
	status_ = 0;
	scale_ = SCALE_NO;
}


bool Object::isImmortal()
{
	return (*currentImmortalStatus_)();
}



bool Object::isTouchable()
{
	return (*currentTouchableStatus_)();
}



bool Object::isShootable()
{
	return (*currentShootableStatus_)();
}



bool Object::propertiesYes()
{
	return true;
}


bool Object::propertiesNo()
{
	return false;
}


void Object::activate(int properties)
{
	switch (properties)
	{
	case PROPERTIES_EVATION:
		currentShootableStatus_ = &Object::propertiesNo;
		break;

	case PROPERTIES_IMMORTAL:
		currentImmortalStatus_ = &Object::propertiesYes;
		break;

	case PROPERTIES_VISIBLE:
		currentTouchableStatus_ = &Object::propertiesYes;
		break;

	default:
		break;
	}
}


void Object::deactivate(int properties)
{
	switch (properties)
	{
	case PROPERTIES_EVATION:
		currentShootableStatus_ = &Object::propertiesYes;
		break;

	case PROPERTIES_IMMORTAL:
		currentImmortalStatus_ = &Object::propertiesNo;
		break;

	case PROPERTIES_VISIBLE:
		currentTouchableStatus_ = &Object::propertiesNo;
		break;

	default:
		break;
	}
}


void Object::switchStatusTo(unsigned int newStatus)
{
	if (status_ != newStatus) {
		sprites_[status_]->reset();
		status_ = newStatus;
	}
}



void Object::loadObjectResource(int numOfSprite, tstring spriteLink)
{
	nSprite_ = numOfSprite;
	fstream file(spriteLink + INFO_FILE);
	if (file.is_open()) {
		sprites_ = new T6_Texture*[numOfSprite];
		FOR(numOfSprite)
			sprites_[i] = new T6_Sprite((spriteLink + Default::tostr(i) + EXTENSION_PICTURE).c_str(), file);

		file.close();
	}
	else {
		WARNING_BOX("Cannot open file\n" << spriteLink);
	}
}



void Object::loadObjectResource(const tchar* path, int rows, int columns, int prettiesResourceType)
{
	nSprite_ = 1;
	resourceType_ = prettiesResourceType;

	sprites_ = new T6_Texture*();

	switch (prettiesResourceType)
	{
	case RESOURCE_MT:
		*sprites_ = new T6_MergedTexture(path, columns, rows);
		break;
	case RESOURCE_MS:
		*sprites_ = new T6_Sprite(path, columns, rows);
		break;
	default:
		break;
	}
}



void Object::setScale(T6Vec2 newScale)
{
	scale_ = newScale;
}


T6Vec3 Object::getPosition()
{
	return this->position_;
}


void Object::fixPosition(T6Vec3 fixDistance)
{
	position_ += fixDistance;
	Default::moveT6Rect(*objectDefRect_, fixDistance);
}


T6_Texture* Object::getCurrentSprite()
{
	return sprites_[status_];
}


T6Rect Object::getRect()
{
	return *Object::objectDefRect_;
}


T6Vec3* Object::getVelo()
{
	return &SPEED_NO;
}


T6Vec2 Object::getScale()
{
	return scale_;
}


bool Object::checkIfCurrentSpriteIs(int spriteIndex)
{
	return (spriteIndex == status_);
}

void Object::setPosition(T6Vec3 newPos)
{
	position_ = newPos;
}
