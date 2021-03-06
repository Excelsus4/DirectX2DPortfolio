#include "stdafx.h"
#include "TurretController.h"
#include "ECS/Entity.h"
#include "ECS/World.h"
#include "ECS/Components/Transform.h"

TurretController::TurretController(Entity * entity, float rotSpeed, float fireDelay, float cooltime):
	Component(entity), rotSpeed(rotSpeed), fireDelay(fireDelay), cooltime(cooltime)
{
}

TurretController::TurretController(Entity * entity):
	Component(entity), rotSpeed(1.0f), fireDelay(0.5f), cooltime(0.0f)
{
}

TurretController::~TurretController()
{
}

void TurretController::PhysicsUpdate(World * world)
{
	Transform* transform = parent->GetTransform();
	Entity* user = world->GetUserEntity();
	if (user != nullptr) {
		// Aim Toward User Entity
		D3DXVECTOR2 delta = user->GetTransform()->Position() - transform->Position();
		float a = atan(delta.x / delta.y) + ((delta.y > 0) ? Math::PI : 0.0f);

		// Linear rotation...
		transform->RotationRadLerp(-a, rotSpeed*Timer->Elapsed());
	}

	cooltime += Timer->Elapsed();
	if (cooltime >= fireDelay) {
		cooltime -= fireDelay;
		parent->SpecialScript(world, 0x744);
	}
}
