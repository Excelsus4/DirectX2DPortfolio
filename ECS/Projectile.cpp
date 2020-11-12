#include "stdafx.h"
#include "Projectile.h"
#include "World.h"
#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "Prefab/Explosion_Hydra.h"

Projectile::Projectile(Entity * entity):
	Component(entity)
{
}

Projectile::~Projectile()
{
}

void Projectile::SetEnemyLayer(int layerIDX)
{
	targetLayer.push_back(layerIDX);
}

void Projectile::PhysicsUpdate(World * world)
{
	for (int i : targetLayer) {
		for (auto e : world->GetLayer(i)->entity) {
			// collision check on these...
			if (parent->GetCollider()->Obb(e->GetCollider())) {
				Entity* temp = new Explosion_Hydra(world->pool);
				world->GetLayer(temp)->instantiateBuffer.push_back(temp);
				temp->GetTransform()->Position(parent->GetTransform()->Position());
				world->GetLayer(parent)->trashBuffer.push_back(parent);

				//TODO: call Target's damager
			}
			
		}
	}
}
