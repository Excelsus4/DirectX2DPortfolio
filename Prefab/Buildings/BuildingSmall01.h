#pragma once
#include "ECS/Entity.h"
#include "Renders/AnimationPool.h"

class BuildingSmall01 : public Entity{
public:
	BuildingSmall01(AnimationPool* pool);
	virtual ~BuildingSmall01();

	virtual void SpecialScript(class World* world, int idx) override;
private:
	class AnimRenderer* mainAnim;
	class Damager* damager;
	int phase;
};