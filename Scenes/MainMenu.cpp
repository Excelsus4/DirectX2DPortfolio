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
	//�ӱ��� ��ư �ΰ�...
	if (ImGui::Button("Play Game")) {
		values->Callback(new Loading(values));
	}

	if (ImGui::Button("Map Editor")) {

	}
}
