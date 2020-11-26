#include "stdafx.h"
#include "Layer.h"
#include "World.h"
#include "Entity.h"

int Layer::GetLayerIDX(string name)
{
	if (name == "Item")
		return 400;
	else if (name == "Effect")
		return 200;
	else if (name == "User")
		return 100;
	else if (name == "HostileMissile")
		return 80;
	else if (name == "UserMissile")
		return 40;
	else if (name == "Hostile_Turret")
		return 36;
	else if (name == "Building")
		return 30;
	else if (name == "Rubbles")
		return -100;
	return 0;
}

void Layer::ClearLayer(World * world)
{
	for (auto iter = entity.begin(); iter != entity.end(); ++iter) {
		(*iter)->Recycle(world);
		SAFE_DELETE(*iter);
	}
	entity.clear();
}

void Layer::Recycle(World * world)
{
	for (auto iter = trashBuffer.begin(); iter != trashBuffer.end();) {
		// find iter in entities and recycle...
		bool isFound = false;
		for (auto entityIter = entity.begin(); entityIter != entity.end();) {
			if (*iter == *entityIter) {
				(*iter)->Recycle(world);
				SAFE_DELETE(*iter);

				entityIter = entity.erase(entityIter);
				iter = trashBuffer.erase(iter);
				isFound = true;
				break;
			}
			else {
				++entityIter;
			}
		}

		// sometimes the entity is added to the trash buffer twice
		// so the entity sometimes cannot be found...
		// Hence just simply erase the iterator in trash buffer
		if (!isFound) {
			iter = trashBuffer.erase(iter);
		}
	}
}

void Layer::Instantiation()
{
	for (auto iter = instantiateBuffer.begin(); iter != instantiateBuffer.end();) {
		entity.push_back(*iter);
		iter = instantiateBuffer.erase(iter);
	}
}

void Layer::Physics(World * world)
{
	for (auto e : entity)
		e->PhysicsUpdate(world);
}

void Layer::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	for (auto e : entity)
		e->Update(V, P);
}

void Layer::Render()
{
	for (auto e : entity)
		e->Render();
}
