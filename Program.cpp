#include "stdafx.h"
#include "./Systems/Device.h"
#include "./Scenes/Scene.h"
#include "./Viewer/Freedom.h"

#include "./Scenes/MainMenu.h"
#include "./Renders/AnimationPool.h"

SceneValues* values;
vector<Scene*> scenes;
vector<Scene*> buffer;

void AddScene(Scene* newScene) {
	buffer.push_back(newScene);
}

void DeBuffer() {
	if (buffer.size() > 0) {
		delete scenes[0];
		scenes.erase(scenes.begin());
		scenes.push_back(*buffer.begin());
		buffer.erase(buffer.begin());
	}
}

void InitScene() {
	values = new SceneValues();
	values->MainCamera = new Freedom();
	values->Pool = new AnimationPool();
	values->Callback = bind(&AddScene, placeholders::_1);

	D3DXMatrixIdentity(&values->Projection);

	scenes.push_back(new MainMenu(values));
}

void DestroyScene(){
	for (auto scene : scenes)
		SAFE_DELETE(scene);

	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(values);
}

D3DXVECTOR2 horizontal(0, 800), vertical(0, 600);
void Update() {
	values->MainCamera->Update();

	D3DXMatrixOrthoOffCenterLH(&values->Projection, horizontal.x, horizontal.y, vertical.x, vertical.y, -10, 10);

	D3DXMatrixOrthoOffCenterLH(
		&values->Projection,
		(float)Width * -0.5f,
		(float)Width * 0.5f,
		(float)Height * -0.5f,
		(float)Height * 0.5f,
		-10, 10
	);

	DeBuffer();

	for (auto scene : scenes)
		scene->Update();
}

void Render() {
	D3DXCOLOR bgColor = D3DXCOLOR(0.18f, 0.26f, 0.26f, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{

		// ImGui::LabelText("FPS", "%.0f", ImGui::GetIO().Framerate);
		for (auto scene : scenes)
			scene->Render();
	}
	ImGui::Render();

	DirectWrite::GetDC()->BeginDraw();
	{
		wstring text = L"";

		RECT rect;
		rect.left = 20;
		rect.top = 0;
		rect.right = 600;
		rect.bottom = 20;

		text = L"Frame Per Second : " + to_wstring((int)ImGui::GetIO().Framerate);
		DirectWrite::RenderText(text, rect);

		rect.top += 20;
		rect.bottom += 20;

		text = L"Camera Position : ";
		text += to_wstring((int)values->MainCamera->Position().x);
		text += L", ";
		text += to_wstring((int)values->MainCamera->Position().y);
		DirectWrite::RenderText(text, rect);
	}

	DirectWrite::GetDC()->EndDraw();
	SwapChain->Present(0, 0);
}

