#include "stdafx.h"
#include "Helicopter.h"
#include "ECS/AnimRenderer.h"
#include "ECS/PlayerController.h"
#include "ECS/Layer.h"
#include "ECS/Collider.h"
#include "ECS/World.h"
#include "Hydra.h"
#include "ECS/Transform.h"
#include "ECS/Damager.h"
#include "Prefab/Explosion_Hydra.h"

Helicopter::Helicopter(AnimationPool * pool):
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

	PlayerController* pCon = new PlayerController(this);
	components.push_back(pCon);

	Collider* collider = new Collider(this, D3DXVECTOR2(8, 50));
	collider->DrawBound(true);
	components.push_back(collider);

	Damager* damager = new Damager(this, 1);
	components.push_back(damager);
}

Helicopter::~Helicopter()
{
}

void Helicopter::SpecialScript(World * world, int idx)
{
	switch (idx) {
	case 0x444:
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
	case 0x53:
		// On Press Key S
	{
		Entity* temp = new Hydra(world->pool);
		world->GetLayer(temp)->instantiateBuffer.push_back(temp);
		temp->GetTransform()->Acceleration(D3DXVECTOR2(0, 600.0f));
		temp->GetTransform()->Position(GetTransform()->Position());
	}
		break;
	}
}
