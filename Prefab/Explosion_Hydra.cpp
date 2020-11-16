#include "stdafx.h"
#include "Explosion_Hydra.h"
#include "ECS/Layer.h"
#include "ECS/Components/AnimRenderer.h"
#include "ECS/Components/TimedRecycle.h"
#include "ECS/World.h"
#include "ECS/Entity.h"
#include "ECS/Components/Transform.h"

Explosion_Hydra::Explosion_Hydra(AnimationPool * pool, string target, float ttl):
	Entity(Layer::GetLayerIDX("Effect"))
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim(target));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);

	TimedRecycle* timer = new TimedRecycle(this, ttl);
	components.push_back(timer);
}

Explosion_Hydra::~Explosion_Hydra()
{
}
