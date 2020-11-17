#include "stdafx.h"
#include "Damager.h"
#include "ECS/Entity.h"

Damager::Damager(Entity * entity, int hp):
	Component(entity), hp(hp), invincible(false)
{
}

Damager::~Damager()
{
}

bool Damager::Damage(World * world, int Damage)
{
	if (invincible)
		return false;
	hp -= Damage;
	if (hp <= 0) {
		//TODO: DEATH
		parent->SpecialScript(world, 0x444);
	}
	return true;
}

void Damager::SetInvincibility(bool val)
{
	invincible = val;
}

void Damager::SetHealth(int hp)
{
	this->hp = hp;
}

void Damager::ImGuiDisplayHp()
{
	ImGui::LabelText("Armor", "Armor: %d", hp);
}
