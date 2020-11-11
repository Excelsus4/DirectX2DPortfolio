#include "stdafx.h"
#include "Projectile.h"
#include "World.h"

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
			//TODO: collision check on these...

		}
	}
}
