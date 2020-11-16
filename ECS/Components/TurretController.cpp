#include "stdafx.h"
#include "TurretController.h"
#include "ECS/Entity.h"

TurretController::TurretController(Entity * entity):
	Component(entity), rotSpeed(1.0f), fireDelay(5.0f), cooltime(0.0f)
{
}

TurretController::~TurretController()
{
}

void TurretController::PhysicsUpdate(World * world)
{
	cooltime += Timer->Elapsed();
	if (cooltime >= fireDelay) {
		cooltime -= fireDelay;
		parent->SpecialScript(world, 0x744);
	}
}
