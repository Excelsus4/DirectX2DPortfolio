#include "stdafx.h"
#include "MainMenu.h"
#include "Loading.h"

MainMenu::MainMenu(SceneValues * values) :
	Scene(values)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Update()
{
}

void MainMenu::Render()
{
	//임구이 버튼 두개...
	if (ImGui::Button("Play Game")) {
		values->Callback(new Loading(values));
	}

	if (ImGui::Button("Map Editor")) {

	}
}
