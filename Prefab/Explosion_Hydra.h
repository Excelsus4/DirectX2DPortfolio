#pragma once
#include "ECS/Entity.h"
#include "Renders/AnimationPool.h"

class Explosion_Hydra : public Entity {
public:
	Explosion_Hydra(AnimationPool* pool);
	virtual ~Explosion_Hydra();

	virtual void SpecialScript(class World* world, int idx) override;
private:

};