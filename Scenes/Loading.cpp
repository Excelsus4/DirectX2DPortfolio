#include "stdafx.h"
#include "Loading.h"

Loading::Loading(SceneValues * values):
	Scene(values)
{
}

Loading::~Loading()
{
}

void Loading::Update()
{
	values->LoadingFlag = values->Pool->Process();
}

void Loading::Render()
{
	values->Pool->Render();
}
