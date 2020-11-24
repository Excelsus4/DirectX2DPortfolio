#pragma once
#include "Scene.h"

class MainMenu : public Scene {
public:
	MainMenu(SceneValues* values);
	virtual ~MainMenu();

	virtual void Update() override;
	virtual void Render() override;
};