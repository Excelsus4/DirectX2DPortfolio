#include "stdafx.h"
#include "BuildingSmall01.h"
#include "ECS/AnimRenderer.h"
#include "ECS/Damager.h"
#include "ECS/Layer.h"
#include "ECS/Collider.h"

BuildingSmall01::BuildingSmall01(AnimationPool * pool):
	Entity(Layer::GetLayerIDX("Building"))
{
	mainAnim = new AnimRenderer(this);
	mainAnim->SetAnim(pool->GetAnim("Building_Small01"));
	mainAnim->PlayAnim(0);
	components.push_back(mainAnim);

	phase = 2;
	damager = new Damager(this, 60);
	components.push_back(damager);

	Collider* collider = new Collider(this, D3DXVECTOR2(80, 80));
	collider->DrawBound(true);
	components.push_back(collider);
}

BuildingSmall01::~BuildingSmall01()
{
}

void BuildingSmall01::SpecialScript(World * world, int idx)
{
	switch (idx) {
	case 0x444:
		if (phase == 2) {
			//HALF DESTRUCTION
			mainAnim->PlayAnim(1);
			damager->SetHealth(90);
			phase = 1;
		}
		else {
			//TOTAL DESTRUCTION
			mainAnim->PlayAnim(2);
			phase = 0;
		}
		break;
	}
}
