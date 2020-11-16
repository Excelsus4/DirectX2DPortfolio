#include "stdafx.h"
#include "Stage1.h"
#include "Viewer/Following.h"
#include "ECS/World.h"
#include "ECS/Transform.h"
#include "Brush/Brush.h"

#include "Prefab/Helicopter.h"

//Transform* DebugTarget;
//float DebugValue = 0.0f;

Stage1::Stage1(SceneValues * values) :
	Scene(values)
{
	world = new World();
	world->pool = values->Pool;

	Entity* temp = new Helicopter(values->Pool);
	temp->GetTransform()->RotateRad(D3DXVECTOR3(0, 0, Math::ToRadian(180.0f)));
	world->GetLayer(temp)->entity.push_back(temp);

	Brush brush(world, world->pool);
	brush.CreateObject(0x00000001, D3DXVECTOR2(100, 100));
	brush.CreateObject(0x00000001, D3DXVECTOR2(-100, 100));
	brush.CreateObject(0x00000002, D3DXVECTOR2(0, 80));
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

	{
		//DEBUG
		//DebugTarget->RotationRad(D3DXVECTOR3(0, 0, DebugValue));
	}

	// PHYSICS!!!
	world->Physics();

	// UPDATE
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	world->Update(V, P);
}

void Stage1::Render()
{
	//ImGui::SliderFloat("Rotation", (float*)&DebugValue,-20, 20);

	// RENDER
	world->Render();
}