#pragma once
#include "ECS/Entity.h"
#include "Renders/AnimationPool.h"

class EnemyProjectile : public Entity {
public:
	EnemyProjectile(AnimationPool* pool, string target, int damage);
	virtual ~EnemyProjectile();

	virtual void SpecialScript(class World* world, int idx) override;
private:
	
};