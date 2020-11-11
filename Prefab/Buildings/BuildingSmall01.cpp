#include "stdafx.h"
#include "BuildingSmall01.h"
#include "ECS/AnimRenderer.h"
#include "ECS/Damager.h"
#include "ECS/Layer.h"

BuildingSmall01::BuildingSmall01(AnimationPool * pool):
	Entity(Layer::GetLayerIDX("Building"))
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("Building_Small01"));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);

	Damager* damager = new Damager(this, 60);
	components.push_back(damager);
}

BuildingSmall01::~BuildingSmall01()
{
}
