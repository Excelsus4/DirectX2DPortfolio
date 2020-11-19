#pragma once
#include "ECS/Component.h"

class Item : public Component {
public:
	Item(class Entity* entity, float gravity, int itemCode);
	virtual ~Item();

	virtual void PhysicsUpdate(class World* world) override;
private:
	float gravity;
	int itemCode;
};