#include "stdafx.h"
#include "MapEditor.h"
#include "MainMenu.h"
#include "Map/MapData.h"
#include "Brush/Brush.h"
#include "ECS/Entity.h"
#include "ECS/Components/Transform.h"

MapEditor::MapEditor(SceneValues * values) :
	Scene(values)
{
	world = new World();
	world->pool = values->Pool;

	currentBrush = 0;
	brushName = "None";

	brush = new Brush(world, world->pool);

	targetMap = new MapData();
}

MapEditor::~MapEditor()
{
	for (auto e : entityOnHand) {
		e->Recycle(world);
		SAFE_DELETE(e);
	}
	SAFE_DELETE(world);
	SAFE_DELETE(brush);
	SAFE_DELETE(targetMap);
}

void MapEditor::Update()
{
	if (Mouse->Down(0)) {
		brush->CreateObject(currentBrush, GetMousePosAsWorldCord());
	}

	// UPDATE
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	world->Update(V, P);
	UpdateHand(V,P);
}

void MapEditor::Render()
{
	ImGui::LabelText(brushName.c_str(), "%08X", currentBrush);

	if (ImGui::Button("AATurret")) {
		currentBrush = 0x00000001; 
		brushName = brush->GetName(currentBrush);
		ChangeHand(brush->CreateObject(currentBrush));
	}if (ImGui::Button("SmallBuilding01")) {
		currentBrush = 0x00000002; 
		brushName = brush->GetName(currentBrush);
		ChangeHand(brush->CreateObject(currentBrush));
	}

	if (ImGui::Button("Quit Editor")) {
		values->Callback(new MainMenu(values));
	}

	world->Render();
	RenderHand();
}

void MapEditor::ChangeHand(vector<class Entity*> vec)
{
	for (auto e : entityOnHand)
		SAFE_DELETE(e);
	entityOnHand = vec;
}

void MapEditor::UpdateHand(D3DXMATRIX & V, D3DXMATRIX & P)
{
	for (auto e : entityOnHand) {
		D3DXVECTOR2 position = GetMousePosAsWorldCord();
		e->GetTransform()->Position(position);
		e->TransformUpdate();
		e->Update(V, P);
	}
}

void MapEditor::RenderHand()
{
	for (auto e : entityOnHand) {
		e->Render();
	}
}

D3DXVECTOR2 MapEditor::GetMousePosAsWorldCord()
{
	D3DXVECTOR2 position = Mouse->Position();
	position.x = position.x - (float)Width*0.5f;
	position.y = (position.y - (float)Height*0.5f)*-1.0f;
	position = position + values->MainCamera->Position();
	position.x = ((int)position.x / GridSize)*GridSize - hGrid;
	position.y = ((int)position.y / GridSize)*GridSize - hGrid;
	return position;
}
