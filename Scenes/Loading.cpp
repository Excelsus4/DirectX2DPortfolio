#include "stdafx.h"
#include "Loading.h"
#include "Stage1.h"

Loading::Loading(SceneValues * values):
	Scene(values)
{
}

Loading::~Loading()
{
}

void Loading::Update()
{
	if (values->Pool->Process())
		values->Callback(new Stage1(values));
}

void Loading::Render()
{
	values->Pool->Render();
}
