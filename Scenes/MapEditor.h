#pragma once
#include "Scene.h"

class MapEditor : public Scene {
public:
	MapEditor(SceneValues* values);
	virtual ~MapEditor();

	virtual void Update() override;
	virtual void Render() override;
};
