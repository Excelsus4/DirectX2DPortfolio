#include "stdafx.h"
#include "Hydra.h"
#include "ECS/AnimRenderer.h"
#include "ECS/Recycler.h"
#include "ECS/Layer.h"
#include "ECS/Projectile.h"
#include "ECS/Collider.h"

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
	projectile->SetEnemyLayer(Layer::GetLayerIDX("Building"));
	components.push_back(projectile);

	Collider* collider = new Collider(this, D3DXVECTOR2(4, 10));
	collider->DrawBound(true);
	components.push_back(collider);
}

Hydra::~Hydra()
{
}
