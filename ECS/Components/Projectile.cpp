#include "stdafx.h"
#include "Projectile.h"
#include "ECS/World.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "Damager.h"
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

void Projectile::SetDamage(int damage)
{
	this->damage = damage;
}

void Projectile::PhysicsUpdate(World * world)
{
	for (int i : targetLayer) {
		for (auto e : world->GetLayer(i)->entity) {
			// collision check on these...
			if (((Collider*)parent->GetComponent(typeid(Collider).name()))->Obb(((Collider*)e->GetComponent(typeid(Collider).name())))) {
				parent->SpecialScript(world, 0x588);
				// call Target's damager
				((Damager*)e->GetComponent(typeid(Damager).name()))->Damage(world, this->damage);
			}
		}
	}
}
