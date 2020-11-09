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
	entities = new World();
	entities->pool = values->Pool;

	Entity* temp = new Helicopter(values->Pool);
	entities->entity.push_back(temp);
	temp->GetTransform()->RotateRad(D3DXVECTOR3(0,0,Math::ToRadian(180.0f)));
}

Stage1::~Stage1()
{
	SAFE_DELETE(entities);
}

void Stage1::Update()
{
	for (auto iter = entities->instantiateBuffer.begin(); iter != entities->instantiateBuffer.end();) {
		entities->entity.push_back(*iter);
		iter = entities->instantiateBuffer.erase(iter);
	}

	for (auto e : entities->entity)
		e->PhysicsUpdate(entities);

	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	for (auto e : entities->entity)
		e->Update(V, P);
}

void Stage1::Render()
{
	for (auto e : entities->entity)
		e->Render();
}