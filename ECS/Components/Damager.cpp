#include "stdafx.h"
#include "Damager.h"
#include "ECS/Entity.h"

Damager::Damager(Entity * entity, int hp):
	Component(entity), hp(hp)
{
}

Damager::~Damager()
{
}

void Damager::Damage(World * world, int Damage)
{
	hp -= Damage;
	if (hp <= 0) {
		//TODO: DEATH
		parent->SpecialScript(world, 0x444);
	}
}

void Damager::SetHealth(int hp)
{
	this->hp = hp;
}
