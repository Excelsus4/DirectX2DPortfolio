#include "stdafx.h"
#include "MapEditor.h"
#include "MainMenu.h"

MapEditor::MapEditor(SceneValues * values) :
	Scene(values)
{
}

MapEditor::~MapEditor()
{
}

void MapEditor::Update()
{
}

void MapEditor::Render()
{
	if (ImGui::Button("Quit Editor")) {
		values->Callback(new MainMenu(values));
	}
}
