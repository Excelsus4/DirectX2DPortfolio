#include "stdafx.h"
#include "Hydra.h"
#include "ECS/Components/AnimRenderer.h"
#include "ECS/Components/Recycler.h"
#include "ECS/Layer.h"
#include "ECS/Components/Projectile.h"
#include "ECS/Components/Collider.h"
#include "Explosion_Hydra.h"
#include "ECS/World.h"
#include "ECS/Components/Transform.h"

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
	projectile->SetEnemyLayer(Layer::GetLayerIDX("Hostile_Turret"));
	projectile->SetDamage(25);
	components.push_back(projectile);

	Collider* collider = new Collider(this, D3DXVECTOR2(4, 10));
	collider->DrawBound(true);
	components.push_back(collider);
}

Hydra::~Hydra()
{
}

void Hydra::SpecialScript(World * world, int idx)
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
