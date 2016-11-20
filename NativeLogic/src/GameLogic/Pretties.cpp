#include "Pretties.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif


Pretties::Pretties(tstring path, index_t index, size_t rows, size_t columns, T6Vec3 position,
					int resourceType, DrawCenter drawCenter)
{
	Object::setBasicProperties();
	currentImmortalStatus_ = Object::propertiesYes;
	currentShootableStatus_ = Object::propertiesNo;
	currentTouchableStatus_ = Object::propertiesNo;

	Object::loadObjectResource(path.c_str(), rows, columns, resourceType);

	index_ = index;
	position_ = position;

	this->drawCenter_ = drawCenter;

	*this->objectDefRect_ = Default::createRectFromDrawCenter(position_, (*sprites_)->getFrameSize(), drawCenter_);
}


Pretties::Pretties(const Pretties& p)
{
	this->index_ = p.index_;
	this->drawCenter_ = p.drawCenter_;
	this->sprites_ = new T6_Texture*();
	this->objectDefRect_ = new T6Rect(*p.objectDefRect_);
	*sprites_ = p.sprites_[0]->clone();
}


Pretties::~Pretties()
{
}


void Pretties::draw() const
{
	if (index_ > 0)
		((T6_MergedTexture*)(*sprites_))->draw(index_ - 1, position_, drawCenter_);
}


void Pretties::draw()
{
	const Pretties* drawObject = this;
	drawObject->draw();
}


void Pretties::update()
{

}


Pretties* Pretties::clone() const
{
	return new Pretties(*this);
}


Pretties* Pretties::clone(T6Vec3 newPos) const
{
	Pretties* result = this->clone();
	result->position_ = newPos;
	*result->objectDefRect_ = Default::createRectFromDrawCenter(result->position_, (*sprites_)->getFrameSize(), drawCenter_);
	return result;
}

bool Pretties::affect(Object* obj, DWORD key)
{
	return false;
}

bool Pretties::isTerminated()
{
	return false;
}
