#pragma once
#include "stdafx.h"
#include "Viewer/Camera.h"
#include "Renders/AnimationPool.h"

struct SceneValues {
	AnimationPool* Pool;
	class Camera* MainCamera;
	D3DXMATRIX Projection;
};

class Scene {
public:
	Scene(SceneValues* values) {
		this->values = values;
	}
	virtual ~Scene() {};

	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	SceneValues* values;
	class World* entities;
};
