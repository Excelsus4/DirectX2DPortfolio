#include "stdafx.h"
#include "Brush.h"
#include "ECS/Transform.h"

#include "Prefab/Enemy/AATurret.h"
#include "Prefab/Buildings/Rubbles.h"
#include "Prefab/Buildings/BuildingSmall01.h"

Brush::Brush(World * world, AnimationPool * pool):
	world(world), pool(pool)
{
}

Brush::~Brush()
{
}

void Brush::CreateObject(UINT code, D3DXVECTOR2 pos)
{
	Entity* temp;
	switch (code) {
	case 0x00000001:
		// Turret
		temp = new AATurret(pool);
		temp->GetTransform()->Position(pos);
		world->GetLayer(temp)->entity.push_back(temp);

		temp = new Rubbles(pool, "AATurret_Base");
		temp->GetTransform()->Position(pos);
		world->GetLayer(temp)->entity.push_back(temp);
		break;
	case 0x00000002:
		// Small Building
		temp = new BuildingSmall01(pool);
		temp->GetTransform()->Position(pos);
		world->GetLayer(temp)->entity.push_back(temp);
	}
}
