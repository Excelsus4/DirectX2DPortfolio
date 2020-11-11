#pragma once
#include "Component.h"

class Damager : public Component {
public:
	Damager(class Entity* entity, int hp);
	virtual ~Damager();

private:
	int hp;
};