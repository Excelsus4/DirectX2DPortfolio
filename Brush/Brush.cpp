#include "stdafx.h"
#include "Brush.h"
#include "ECS/Components/Transform.h"

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

vector<Entity*> Brush::CreateObject(UINT code)
{
	vector<Entity*> list;
	Entity* temp;
	switch (code) {
	case 0x00000001:
		// Turret
		temp = new Rubbles(pool, "AATurret_Base");
		list.push_back(temp);
		temp = new AATurret(pool);
		list.push_back(temp);
		break;
	case 0x00000002:
		// Small Building
		temp = new BuildingSmall01(pool);
		list.push_back(temp);
		break;
	}
	return list;
}

void Brush::CreateObject(UINT code, D3DXVECTOR2 pos)
{
	vector<Entity*> list = CreateObject(code);
	for (auto e : list) {
		e->GetTransform()->Position(pos);
		e->TransformUpdate();
		world->GetLayer(e)->entity.push_back(e);
	}
}

string Brush::GetName(UINT code)
{
	switch (code) {
	case 0x00000001:
		return "AATurret";
	case 0x00000002:
		return "SmallBuilding01";
	}
	return "None";
}
