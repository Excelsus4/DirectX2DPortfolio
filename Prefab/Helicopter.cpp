#include "stdafx.h"
#include "Helicopter.h"
#include "ECS/Components/AnimRenderer.h"
#include "ECS/Components/PlayerController.h"
#include "ECS/Layer.h"
#include "ECS/Components/Collider.h"
#include "ECS/World.h"
#include "Hydra.h"
#include "Hellfire.h"
#include "Bullet.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Damager.h"
#include "Prefab/Explosion_Hydra.h"

Helicopter::Helicopter(AnimationPool * pool) :
	Entity(Layer::GetLayerIDX("User"))
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("Apache_Body"));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);

	animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("Apache_Rotor"));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);

	animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("Apache_Rotor_FX"));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);

	pCon = new PlayerController(this);
	components.push_back(pCon);

	Collider* collider = new Collider(this, D3DXVECTOR2(8, 50));
	collider->DrawBound(true);
	components.push_back(collider);

	damager = new Damager(this, 1);
	components.push_back(damager);
}

Helicopter::~Helicopter()
{
}

void Helicopter::PhysicsUpdate(World * world)
{
	if (invincibleTime > 0) {
		invincibleTime -= Timer->Elapsed();
		if (invincibleTime <= 0) {
			// Remove invincibility;
			damager->SetInvincibility(false);
		}
	}
	__super::PhysicsUpdate(world);
}

void Helicopter::Render()
{
	if (invincibleTime - (int)invincibleTime < 0.75f)
		__super::Render();
	pCon->ImGuiDisplayAmmo();
	damager->ImGuiDisplayHp();
}

void Helicopter::SpecialScript(World * world, int idx)
{
	switch (idx) {
	case 0x0000444:
		// On HP lower than 0
	{
		world->GetLayer(this)->trashBuffer.push_back(this);

		Entity* temp = new Explosion_Hydra(world->pool, "Explosion_Big01", 0.8f);
		world->GetLayer(temp)->instantiateBuffer.push_back(temp);
		temp->GetTransform()->Position(this->GetTransform()->Position());
		temp->GetTransform()->Scale(this->GetTransform()->Scale());
		temp->GetTransform()->RotationRad(this->GetTransform()->RotationRad());
	}
	break;
	case 0x0100041:
		// On Press Key A
	{
		Entity* temp = new Hellfire(world->pool);
		world->GetLayer(temp)->instantiateBuffer.push_back(temp);
		temp->GetTransform()->Acceleration(D3DXVECTOR2(0, 400.0f));
		temp->GetTransform()->Position(GetTransform()->Position());
	}
	break;
	case 0x0100053:
		// On Press Key S
	{
		Entity* temp = new Hydra(world->pool);
		world->GetLayer(temp)->instantiateBuffer.push_back(temp);
		temp->GetTransform()->Acceleration(D3DXVECTOR2(0, 600.0f));
		temp->GetTransform()->Position(GetTransform()->Position());
	}
	break;
	case 0x0100044:
		// On Press Key D
	{
		Entity* temp = new Bullet(world->pool);
		world->GetLayer(temp)->instantiateBuffer.push_back(temp);
		temp->GetTransform()->Velocity(D3DXVECTOR2(0, 1000.0f));
		temp->GetTransform()->Position(GetTransform()->Position());
	}
	break;
	case 0x8400064:
		// On Gather Coin
	{
		world->score += idx - 0x8400000;
	}
	break;
	}
}

void Helicopter::SetInvincibility(float duration)
{
	//TODO: Set Invincibility
	damager->SetInvincibility(true);
	invincibleTime = duration;
}
