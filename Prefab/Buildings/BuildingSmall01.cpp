#include "stdafx.h"
#include "BuildingSmall01.h"
#include "ECS/Components/AnimRenderer.h"
#include "ECS/Components/Damager.h"
#include "ECS/Layer.h"
#include "ECS/Components/Collider.h"
#include "Rubbles.h"
#include "ECS/World.h"
#include "ECS/Components/Transform.h"
#include "Prefab/Explosion_Hydra.h"

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
			Entity* temp = new Rubbles(world->pool, "Building_Small01_Rubble");
			world->GetLayer(temp)->instantiateBuffer.push_back(temp);
			temp->GetTransform()->Position(this->GetTransform()->Position());
			temp->GetTransform()->Scale(this->GetTransform()->Scale());
			temp->GetTransform()->RotationRad(this->GetTransform()->RotationRad());
			world->GetLayer(this)->trashBuffer.push_back(this);

			temp = new Explosion_Hydra(world->pool, "Explosion_Big01", 0.8f);
			world->GetLayer(temp)->instantiateBuffer.push_back(temp);
			temp->GetTransform()->Position(this->GetTransform()->Position());
			temp->GetTransform()->Scale(this->GetTransform()->Scale());
			temp->GetTransform()->RotationRad(this->GetTransform()->RotationRad());
		}
		break;
	}
}
