#pragma once
#include "Scene.h"

class Loading :public Scene {
public:
	Loading(SceneValues* values);
	virtual ~Loading();

	virtual void Update() override;
	virtual void Render() override;

	bool* flag;
private:
	
};