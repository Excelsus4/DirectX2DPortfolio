#include "stdafx.h"
#include "Helicopter.h"
#include "ECS/AnimRenderer.h"

Helicopter::Helicopter(AnimationPool * pool)
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
}

Helicopter::~Helicopter()
{
}
