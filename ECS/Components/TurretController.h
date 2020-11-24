#pragma once
#include "ECS/Component.h"

class TurretController : public Component {
public:
	TurretController(class Entity* entity, float rotSpeed, float fireDelay, float cooltime);
	TurretController(class Entity* entity);
	virtual ~TurretController();

	virtual void PhysicsUpdate(class World* world) override;

private:
	float rotSpeed;
	float fireDelay;
	float cooltime;
};