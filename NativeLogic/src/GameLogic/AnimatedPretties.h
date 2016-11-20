#ifndef __ANIMATED_PRETTIES_H__
#define __ANIMATED_PRETTIES_H__

#include "Pretties.h"

class AnimatedPretties : virtual public Pretties
{
public:
	AnimatedPretties(tstring path, index_t index, size_t rows, T6Vec3 position, int frameNum);
	~AnimatedPretties();

	void draw();
	void update();

private:
	int frameNum_;
};

#endif