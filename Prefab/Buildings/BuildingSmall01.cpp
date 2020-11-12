#include "stdafx.h"
#include "BuildingSmall01.h"
#include "ECS/AnimRenderer.h"
#include "ECS/Damager.h"
#include "ECS/Layer.h"
#include "ECS/Collider.h"

BuildingSmall01::BuildingSmall01(AnimationPool * pool):
	Entity(Layer::GetLayerIDX("Building"))
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("Building_Small01"));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);

	Damager* damager = new Damager(this, 60);
	components.push_back(damager);

	Collider* collider = new Collider(this, D3DXVECTOR2(96, 96));
	collider->DrawBound(true);
	components.push_back(collider);
}

BuildingSmall01::~BuildingSmall01()
{
}
