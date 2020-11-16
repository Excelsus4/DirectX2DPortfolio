#include "stdafx.h"
#include "AATurret.h"
#include "ECS/Layer.h"
#include "ECS/Components/AnimRenderer.h"
#include "ECS/Components/Collider.h"
#include "ECS/Components/Damager.h"
#include "ECS/Components/TurretController.h"
#include "EnemyProjectile.h"
#include "ECS/World.h"
#include "ECS/Components/Transform.h"
#include "Prefab/Explosion_Hydra.h"

AATurret::AATurret(AnimationPool * pool) :
	Entity(Layer::GetLayerIDX("Hostile_Turret"))
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("AATurret"));
	animRenderer->PlayAnim(0);
	animRenderer->SpriteBasedRotation(true, 16);
	components.push_back(animRenderer);

	Damager* damager = new Damager(this, 60);
	components.push_back(damager);

	Collider* collider = new Collider(this, D3DXVECTOR2(34, 34));
	collider->DrawBound(true);
	components.push_back(collider);

	TurretController* controller = new TurretController(this);
	components.push_back(controller);
}

AATurret::~AATurret()
{
}

void AATurret::SpecialScript(World * world, int idx)
{
	switch (idx) {
	case 0x0000744:
	{
		// TurretController's Attack Action
		Entity* temp = new EnemyProjectile(world->pool, "Missile_Hydra", 5);
		world->GetLayer(temp)->instantiateBuffer.push_back(temp);
		// set the velocity to a local form
		float theta = GetTransform()->RotationRad().z + Math::PI;
		temp->GetTransform()->RotationRad(D3DXVECTOR3(0, 0, theta));
		temp->GetTransform()->Velocity(D3DXVECTOR2(-sin(theta), cos(theta))*100.0f);
		temp->GetTransform()->Position(GetTransform()->Position());
	}
		break;
	case 0x0000444:
	{
		// On Death
		Entity* temp = new Explosion_Hydra(world->pool, "Explosion_Big01", 0.8f);
		world->GetLayer(temp)->instantiateBuffer.push_back(temp);
		temp->GetTransform()->Position(this->GetTransform()->Position());
		temp->GetTransform()->Scale(this->GetTransform()->Scale());
		temp->GetTransform()->RotationRad(this->GetTransform()->RotationRad());
		world->GetLayer(this)->trashBuffer.push_back(this);
	}
		break;
	}
}
