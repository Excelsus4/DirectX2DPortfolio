#include "stdafx.h"
#include "Recycler.h"
#include "World.h"
#include "Entity.h"
#include "Transform.h"

Recycler::Recycler(class Entity* entity):
	Component(entity)
{
}

Recycler::~Recycler()
{
}

void Recycler::PhysicsUpdate(World * world)
{
	//if transform is out somewhere, then add it to world->trashBuffer
	D3DXVECTOR2 pos = parent->GetTransform()->Position();
	//TODO: Fix this criteria on where is "Out somewhere", For now it is temporary
	if (pos.y > 1000) {
		world->trashBuffer.push_back(parent);
	}
}