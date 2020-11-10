#include "stdafx.h"
#include "Stage1.h"
#include "Viewer/Following.h"
#include "ECS/World.h"
#include "ECS/Transform.h"

#include "Prefab/Helicopter.h"
#include "Prefab/Hydra.h"

Stage1::Stage1(SceneValues * values) :
	Scene(values)
{
	world = new World();
	world->pool = values->Pool;

	Entity* temp = new Helicopter(values->Pool);
	world->entity.push_back(temp);
	temp->GetTransform()->RotateRad(D3DXVECTOR3(0,0,Math::ToRadian(180.0f)));
}

Stage1::~Stage1()
{
	SAFE_DELETE(world);
}

void Stage1::Update()
{
	// Recycle Code...
	for (auto iter = world->trashBuffer.begin(); iter != world->trashBuffer.end();) {
		// find iter in entities and recycle...
		for (auto entityIter = world->entity.begin(); entityIter != world->entity.end();) {
			if (*iter == *entityIter) {
				(*iter)->Recycle(world);
				SAFE_DELETE(*iter);

				entityIter = world->entity.erase(entityIter);
				iter = world->trashBuffer.erase(iter);
				break;
			}
			else {
				entityIter++;
			}
		}
	}

	// Instantiation Code...
	for (auto iter = world->instantiateBuffer.begin(); iter != world->instantiateBuffer.end();) {
		world->entity.push_back(*iter);
		iter = world->instantiateBuffer.erase(iter);
	}

	// PHYSICS!!!
	for (auto e : world->entity)
		e->PhysicsUpdate(world);

	// UPDATE
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	for (auto e : world->entity)
		e->Update(V, P);
}

void Stage1::Render()
{
	// RENDER
	for (auto e : world->entity)
		e->Render();
}