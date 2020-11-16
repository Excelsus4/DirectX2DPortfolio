#pragma once
#include "ECS/Component.h"

class Recycler : public Component{
public:
	Recycler(class Entity* entity);
	virtual ~Recycler();

	virtual void PhysicsUpdate(class World* world) override;
};