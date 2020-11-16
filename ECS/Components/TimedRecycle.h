#pragma once
#include "ECS/Component.h"

class TimedRecycle :public Component {
public:
	TimedRecycle(class Entity* entity, float ttl);
	virtual ~TimedRecycle();

	virtual void PhysicsUpdate(class World* world) override;

private:
	float ttl;
	float age;
};