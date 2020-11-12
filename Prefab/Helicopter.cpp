#include "stdafx.h"
#include "Helicopter.h"
#include "ECS/AnimRenderer.h"
#include "ECS/PlayerController.h"
#include "ECS/Layer.h"
#include "ECS/Collider.h"

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

	Collider* collider = new Collider(this, D3DXVECTOR2(24, 60));
	collider->DrawBound(true);
	components.push_back(collider);
}

Helicopter::~Helicopter()
{
}
