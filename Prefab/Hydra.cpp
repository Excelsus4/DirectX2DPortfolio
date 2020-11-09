#include "stdafx.h"
#include "Hydra.h"
#include "ECS/AnimRenderer.h"

Hydra::Hydra(AnimationPool * pool)
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("Missile_Hydra"));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);
}

Hydra::~Hydra()
{
}
