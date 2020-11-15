#pragma once
#include "ECS/Entity.h"
#include "Renders/AnimationPool.h"

class Rubbles : public Entity {
public:
	Rubbles(AnimationPool* pool, string target);
	virtual ~Rubbles();
};