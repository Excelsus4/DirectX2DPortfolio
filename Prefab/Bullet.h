#pragma once
#include "ECS/Entity.h"
#include "Renders/AnimationPool.h"

class Bullet :public Entity {
public:
	Bullet(AnimationPool* pool);
	virtual ~Bullet();

	virtual void SpecialScript(class World* world, int idx) override;
private:
};