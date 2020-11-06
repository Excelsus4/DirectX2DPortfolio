#include "stdafx.h"
#include "Stage1.h"
#include "Viewer/Following.h"
#include "ECS/World.h"
#include "Prefab/Helicopter.h"

Stage1::Stage1(SceneValues * values) :
	Scene(values)
{
	entities = new World();
	entities->entity.push_back(new Helicopter(values->Pool));
}

Stage1::~Stage1()
{
	SAFE_DELETE(entities);
}

void Stage1::Update()
{
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