#pragma once
#include "ECS/Entity.h"
#include "Renders/AnimationPool.h"

class Helicopter : public Entity{
public:
	Helicopter(AnimationPool* pool);
	virtual ~Helicopter();

	virtual void SpecialScript(class World* world, int idx) override;
private:

};