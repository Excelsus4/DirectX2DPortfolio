#pragma once
#include "ECS/Entity.h"
#include "Renders/AnimationPool.h"

class Explosion_Hydra : public Entity {
public:
	Explosion_Hydra(AnimationPool* pool, string target, float ttl);
	virtual ~Explosion_Hydra();
private:

};