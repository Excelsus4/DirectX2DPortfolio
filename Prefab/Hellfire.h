#pragma once
#include "ECS/Entity.h"
#include "Renders/AnimationPool.h"

class Hellfire : public Entity {
public:
	Hellfire(AnimationPool* pool);
	virtual ~Hellfire();

	virtual void SpecialScript(class World* world, int idx) override;
private:

};