#pragma once
#include "Scene.h"

class MapEditor : public Scene {
public:
	MapEditor(SceneValues* values);
	virtual ~MapEditor();

	virtual void Update() override;
	virtual void Render() override;

private:
	class Brush* brush;
	class MapData* targetMap;
	int currentBrush;
	string brushName;

	const int GridSize = 32;
	const float hGrid = 16.0f;

private:
	void ChangeHand(vector<class Entity*> vec);
	void UpdateHand(D3DXMATRIX& V, D3DXMATRIX& P);
	void RenderHand();
	D3DXVECTOR2 GetMousePosAsWorldCord();

	vector<class Entity*> entityOnHand;
};
