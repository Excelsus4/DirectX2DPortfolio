#pragma once
#include "Component.h"

class Damager : public Component {
public:
	Damager(class Entity* entity, int hp);
	virtual ~Damager();

	void Damage(World * world, int Damage);
	void SetHealth(int hp);

private:
	int hp;
};