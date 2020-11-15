#pragma once
#include "ECS/Entity.h"
#include "Renders/AnimationPool.h"

class AATurret :public Entity {
public:
	AATurret(AnimationPool* pool);
	virtual ~AATurret();

	virtual void SpecialScript(class World* world, int idx) override;
private:
	
};