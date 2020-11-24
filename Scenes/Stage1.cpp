#include "stdafx.h"
#include "Stage1.h"
#include "Viewer/Following.h"
#include "ECS/World.h"
#include "ECS/Components/Transform.h"
#include "Brush/Brush.h"

#include "Prefab/Helicopter.h"
#include "Prefab/Item/Score.h"

//Transform* DebugTarget;
//float DebugValue = 0.0f;

Stage1::Stage1(SceneValues * values) :
	Scene(values)
{
	world = new World();
	world->pool = values->Pool;
	world->life = 4;
	world->ScrollSpeed = -20;
	world->ScrollLayers.push_back(Layer::GetLayerIDX("Building"));
	world->ScrollLayers.push_back(Layer::GetLayerIDX("Hostile_Turret"));
	world->ScrollLayers.push_back(Layer::GetLayerIDX("Rubbles"));

	RECT scSize;
	scSize.left = -200;
	scSize.right = 200;
	scSize.top = 300;
	scSize.bottom = -300;
	world->screenSize = scSize;

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

	if (world->GetLayer(Layer::GetLayerIDX("User"))->entity.size() <= 0) {
		CreateHeli();
	}

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

	// Player Global Data (Those That aren't bound to helicopter)
	ImGui::LabelText("Lives", "%d", world->life);
	ImGui::LabelText("Score", "%d", world->score);
}

void Stage1::CreateHeli()
{
	if (world->life > 0) {
		--world->life;
		Helicopter* temp = new Helicopter(values->Pool);
		temp->GetTransform()->Position(D3DXVECTOR2(0, -200));
		temp->GetTransform()->RotateRad(D3DXVECTOR3(0, 0, Math::ToRadian(180.0f)));
		temp->SetInvincibility(5.0f);
		world->GetLayer(temp)->entity.push_back(temp);
	}
}
