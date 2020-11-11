#pragma once
#include "Layer.h"

class World {
public:
	World();
	virtual ~World();

	Layer* GetLayer(class Entity* entity);
	void Recycle();
	void Instantiation();
	void Physics();
	void Update(D3DXMATRIX & V, D3DXMATRIX & P);
	void Render();

public:
	map<int, Layer*> layers;
	class AnimationPool* pool;
};