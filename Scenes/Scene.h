#pragma once
#include "stdafx.h"
#include "Viewer/Camera.h"
#include "Renders/AnimationPool.h"

struct SceneValues {
	AnimationPool* Pool;
	class Camera* MainCamera;
	D3DXMATRIX Projection;
	function<void(class Scene*)> Callback;
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
	class World* world;
};
