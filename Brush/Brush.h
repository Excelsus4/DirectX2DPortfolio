#pragma once
#include "ECS/World.h"
#include "Renders/AnimationPool.h"

class Brush {
public:
	Brush(World* world, AnimationPool* pool);
	virtual ~Brush();

	void CreateObject(UINT code, D3DXVECTOR2 pos);

private:
	World* world;
	AnimationPool* pool;
};