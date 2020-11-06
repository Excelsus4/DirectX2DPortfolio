#pragma once
#include "Component.h"

class PlayerController :public Component {
public:
	PlayerController(class Entity* entity);
	virtual ~PlayerController();

	virtual void PhysicsUpdate(class World* world) override;

private:
	float speed;
	float roll;
	float pitch;

};