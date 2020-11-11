#include "stdafx.h"
#include "BuildingSmall01.h"
#include "ECS/AnimRenderer.h"

BuildingSmall01::BuildingSmall01(AnimationPool * pool)
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("Building_Small01"));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);
}

BuildingSmall01::~BuildingSmall01()
{
}
