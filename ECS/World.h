#pragma once
#include "Layer.h"

class World {
public:
	World();
	virtual ~World();

	Layer* GetLayer(class Entity* entity);
	Layer* GetLayer(int layerIDX);

	void Recycle();
	void Instantiation();
	void Physics();
	void Update(D3DXMATRIX & V, D3DXMATRIX & P);
	void Render();

public:
	class AnimationPool* pool;

private:
	map<int, Layer*> layers;
};