#include "stdafx.h"
#include "AATurret.h"
#include "ECS/Layer.h"
#include "ECS/AnimRenderer.h"
#include "ECS/Collider.h"
#include "ECS/Damager.h"

AATurret::AATurret(AnimationPool * pool):
	Entity(Layer::GetLayerIDX("Hostile_Turret"))
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("AATurret"));
	animRenderer->PlayAnim(0);
	animRenderer->SpriteBasedRotation(true, 16);
	components.push_back(animRenderer);

	Damager* damager = new Damager(this, 60);
	components.push_back(damager);

	Collider* collider = new Collider(this, D3DXVECTOR2(34, 34));
	collider->DrawBound(true);
	components.push_back(collider);
}

AATurret::~AATurret()
{
}

void AATurret::SpecialScript(World * world, int idx)
{
}
