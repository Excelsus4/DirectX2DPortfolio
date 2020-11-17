#pragma once
#include "ECS/Component.h"

class PlayerController :public Component {
public:
	PlayerController(class Entity* entity);
	virtual ~PlayerController();

	virtual void PhysicsUpdate(class World* world) override;

	void ImGuiDisplayAmmo();
private:
	float speed;
	float roll;
	float pitch;

	float attackspeed;
	float cooltime;

	int ammo[3];
};