#pragma once
#include "ECS/Entity.h"
#include "Renders/AnimationPool.h"

class Helicopter : public Entity{
public:
	Helicopter(AnimationPool* pool);
	virtual ~Helicopter();

	virtual void PhysicsUpdate(class World* world) override;
	virtual void Render() override;

	virtual void SpecialScript(class World* world, int idx) override;

	void SetInvincibility(float duration);
private:
	class PlayerController* pCon;
	class Damager* damager;

	float invincibleTime;
};