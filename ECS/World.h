#pragma once
#include "Layer.h"

class World {
public:
	World();
	virtual ~World();

	Layer* GetLayer(class Entity* entity);
	Layer* GetLayer(int layerIDX);

	void ClearWorld();
	void Recycle();
	void Instantiation();
	void Physics();
	void Update(D3DXMATRIX & V, D3DXMATRIX & P);
	void Render();

	class Entity* GetUserEntity();
public:
	class AnimationPool* pool;
	RECT screenSize;

private:
	map<int, Layer*> layers;

public:
	int life;
	int score;

	vector<int> ScrollLayers;
	float ScrollSpeed;
};