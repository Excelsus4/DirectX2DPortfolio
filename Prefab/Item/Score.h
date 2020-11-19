#pragma once
#include "ECS/Entity.h"
#include "Renders/AnimationPool.h"

class Score : public Entity {
public:
	Score(AnimationPool* pool);
	virtual ~Score();
private:

};