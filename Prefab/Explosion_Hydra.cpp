#include "stdafx.h"
#include "Explosion_Hydra.h"
#include "ECS/Layer.h"
#include "ECS/AnimRenderer.h"
#include "ECS/TimedRecycle.h"

Explosion_Hydra::Explosion_Hydra(AnimationPool * pool):
	Entity(Layer::GetLayerIDX("Effect"))
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("Explosion_Small01"));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);

	TimedRecycle* timer = new TimedRecycle(this, 0.8f);
	components.push_back(timer);
}

Explosion_Hydra::~Explosion_Hydra()
{
}
