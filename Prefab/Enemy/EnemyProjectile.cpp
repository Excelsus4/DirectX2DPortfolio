#include "stdafx.h"
#include "EnemyProjectile.h"
#include "ECS/Layer.h"
#include "ECS/AnimRenderer.h"
#include "ECS/Recycler.h"
#include "ECS/Projectile.h"
#include "ECS/Collider.h"

EnemyProjectile::EnemyProjectile(AnimationPool * pool, string target, int damage):
	Entity(Layer::GetLayerIDX("HostileMissile"))
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("Missile_Hydra"));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);

	Recycler* recycler = new Recycler(this);
	components.push_back(recycler);

	/*Projectile* projectile = new Projectile(this);
	projectile->SetEnemyLayer(Layer::GetLayerIDX("User"));
	projectile->SetDamage(damage);
	components.push_back(projectile);

	Collider* collider = new Collider(this, D3DXVECTOR2(2, 2));
	collider->DrawBound(true);
	components.push_back(collider);*/
}

EnemyProjectile::~EnemyProjectile()
{
}

void EnemyProjectile::SpecialScript(World * world, int idx)
{
}
