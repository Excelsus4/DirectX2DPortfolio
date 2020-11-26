#pragma once
#include "ECS/World.h"
#include "Renders/AnimationPool.h"

class Brush {
public:
	Brush(World* world, AnimationPool* pool);
	virtual ~Brush();

	vector<class Entity*> CreateObject(UINT code);
	void CreateObject(UINT code, D3DXVECTOR2 pos);
	string GetName(UINT code);
private:
	World* world;
	AnimationPool* pool;
};