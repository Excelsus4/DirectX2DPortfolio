#include "stdafx.h"
#include "Stage1.h"
#include "Viewer/Following.h"
#include "ECS/World.h"
#include "ECS/Transform.h"

#include "Prefab/Helicopter.h"
#include "Prefab/Buildings/BuildingSmall01.h"

Stage1::Stage1(SceneValues * values) :
	Scene(values)
{
	world = new World();
	world->pool = values->Pool;

	Entity* temp = new Helicopter(values->Pool);
	temp->GetTransform()->RotateRad(D3DXVECTOR3(0, 0, Math::ToRadian(180.0f)));
	world->GetLayer(temp)->entity.push_back(temp);

	temp = new BuildingSmall01(values->Pool);
	world->GetLayer(temp)->entity.push_back(temp);
}

Stage1::~Stage1()
{
	SAFE_DELETE(world);
}

void Stage1::Update()
{
	// Recycle Code...
	world->Recycle();

	// Instantiation Code...
	world->Instantiation();

	// PHYSICS!!!
	world->Physics();

	// UPDATE
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	world->Update(V, P);
}

void Stage1::Render()
{
	// RENDER
	world->Render();
}