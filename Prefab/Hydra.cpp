#include "stdafx.h"
#include "Hydra.h"
#include "ECS/AnimRenderer.h"
#include "ECS/Recycler.h"
#include "ECS/Layer.h"
#include "ECS/Projectile.h"

Hydra::Hydra(AnimationPool * pool):
	Entity(Layer::GetLayerIDX("UserMissile"))
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("Missile_Hydra"));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);

	Recycler* recycler = new Recycler(this);
	components.push_back(recycler);

	Projectile* projectile = new Projectile(this);
	components.push_back(projectile);
}

Hydra::~Hydra()
{
}
