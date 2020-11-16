#include "stdafx.h"
#include "Hellfire.h"
#include "ECS/Layer.h"
#include "ECS/Components/AnimRenderer.h"
#include "ECS/Components/Recycler.h"
#include "ECS/Components/Projectile.h"
#include "ECS/Components/Collider.h"
#include "Explosion_Hydra.h"
#include "ECS/World.h"
#include "ECS/Components/Transform.h"

Hellfire::Hellfire(AnimationPool * pool):
	Entity(Layer::GetLayerIDX("UserMissile"))
{
	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("Missile_Hellfire"));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);

	Recycler* recycler = new Recycler(this);
	components.push_back(recycler);

	Projectile* projectile = new Projectile(this);
	projectile->SetEnemyLayer(Layer::GetLayerIDX("Building"));
	projectile->SetEnemyLayer(Layer::GetLayerIDX("Hostile_Turret"));
	projectile->SetDamage(100);
	components.push_back(projectile);

	Collider* collider = new Collider(this, D3DXVECTOR2(10, 20));
	collider->DrawBound(true);
	components.push_back(collider);
}

Hellfire::~Hellfire()
{
}

void Hellfire::SpecialScript(World * world, int idx)
{
	switch (idx) {
	case 0x0000588:
		// On Projectile Hit
		Entity* temp = new Explosion_Hydra(world->pool, "Explosion_Medium01", 0.8f);
		world->GetLayer(temp)->instantiateBuffer.push_back(temp);
		temp->GetTransform()->Position(this->GetTransform()->Position());
		world->GetLayer(this)->trashBuffer.push_back(this);
		break;
	}
}
