#include "stdafx.h"
#include "Helicopter.h"
#include "ECS/AnimRenderer.h"
#include "ECS/PlayerController.h"
#include "ECS/Layer.h"
#include "ECS/Collider.h"
#include "ECS/World.h"
#include "Hydra.h"
#include "ECS/Transform.h"

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
}

Helicopter::~Helicopter()
{
}

void Helicopter::SpecialScript(World * world, int idx)
{
	switch (idx) {
	case 0x53:
		Entity* temp = new Hydra(world->pool);
		world->GetLayer(temp)->instantiateBuffer.push_back(temp);
		temp->GetTransform()->Acceleration(D3DXVECTOR2(0, 600.0f));
		temp->GetTransform()->Position(GetTransform()->Position());
		break;
	}
}
