#include "stdafx.h"
#include "Bullet.h"
#include "ECS/AnimRenderer.h"
#include "ECS/Recycler.h"
#include "ECS/Layer.h"
#include "ECS/Projectile.h"
#include "ECS/Collider.h"
#include "ECS/World.h"
#include "Explosion_Hydra.h"
#include "ECS/Transform.h"

Bullet::Bullet(AnimationPool * pool):
Entity(Layer::GetLayerIDX("UserMissile"))
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("Missile_Bullet"));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);

	Recycler* recycler = new Recycler(this);
	components.push_back(recycler);

	Projectile* projectile = new Projectile(this);
	projectile->SetEnemyLayer(Layer::GetLayerIDX("Building"));
	projectile->SetEnemyLayer(Layer::GetLayerIDX("Hostile_Turret"));
	projectile->SetDamage(1);
	components.push_back(projectile);

	Collider* collider = new Collider(this, D3DXVECTOR2(2, 2));
	collider->DrawBound(true);
	components.push_back(collider);
}

Bullet::~Bullet()
{
}

void Bullet::SpecialScript(World * world, int idx)
{
	switch (idx) {
	case 0x0000588:
		// On Projectile Hit
		Entity* temp = new Explosion_Hydra(world->pool, "Explosion_Small01", 0.8f);
		world->GetLayer(temp)->instantiateBuffer.push_back(temp);
		temp->GetTransform()->Position(this->GetTransform()->Position());
		world->GetLayer(this)->trashBuffer.push_back(this);
		break;
	}
}
