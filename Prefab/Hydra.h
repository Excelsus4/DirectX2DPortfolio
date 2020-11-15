#pragma once
#include "ECS/Entity.h"
#include "Renders/AnimationPool.h"

class Hydra : public Entity {
public:
	Hydra(AnimationPool* pool);
	virtual ~Hydra();

	virtual void SpecialScript(class World* world, int idx) override;
private:

};