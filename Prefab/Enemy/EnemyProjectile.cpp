#include "stdafx.h"
#include "EnemyProjectile.h"
#include "ECS/Layer.h"
#include "ECS/Components/AnimRenderer.h"
#include "ECS/Components/Recycler.h"
#include "ECS/Components/Projectile.h"
#include "ECS/Components/Collider.h"
#include "Prefab/Explosion_Hydra.h"
#include "ECS/World.h"
#include "ECS/Components/Transform.h"

EnemyProjectile::EnemyProjectile(AnimationPool * pool, string target, int damage):
	Entity(Layer::GetLayerIDX("HostileMissile"))
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("Missile_Hydra"));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);

	Recycler* recycler = new Recycler(this);
	components.push_back(recycler);

	Projectile* projectile = new Projectile(this);
	projectile->SetEnemyLayer(Layer::GetLayerIDX("User"));
	projectile->SetDamage(damage);
	components.push_back(projectile);

	Collider* collider = new Collider(this, D3DXVECTOR2(2, 2));
	collider->DrawBound(true);
	components.push_back(collider);
}

EnemyProjectile::~EnemyProjectile()
{
}

void EnemyProjectile::SpecialScript(World * world, int idx)
{
	switch (idx) {
	case 0x588:
		Entity* temp = new Explosion_Hydra(world->pool, "Explosion_Small01", 0.8f);
		world->GetLayer(temp)->instantiateBuffer.push_back(temp);
		temp->GetTransform()->Position(this->GetTransform()->Position());
		world->GetLayer(this)->trashBuffer.push_back(this);
		break;
	}
}
