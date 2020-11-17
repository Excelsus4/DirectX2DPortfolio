#pragma once
#include "ECS/Component.h"

class Damager : public Component {
public:
	Damager(class Entity* entity, int hp);
	virtual ~Damager();

	bool Damage(World * world, int Damage);
	void SetInvincibility(bool val);
	void SetHealth(int hp);

	void ImGuiDisplayHp();
private:
	bool invincible;
	int hp;
};