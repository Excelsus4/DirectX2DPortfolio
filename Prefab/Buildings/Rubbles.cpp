#include "stdafx.h"
#include "Rubbles.h"
#include "ECS/Layer.h"
#include "ECS/AnimRenderer.h"

Rubbles::Rubbles(AnimationPool * pool, string target):
	Entity(Layer::GetLayerIDX("Rubbles"))
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim(target));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);
}

Rubbles::~Rubbles()
{
}
