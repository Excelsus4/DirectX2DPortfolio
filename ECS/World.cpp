#include "stdafx.h"
#include "World.h"
#include "Entity.h"

World::World()
{
}

World::~World()
{
}

Layer * World::GetLayer(Entity * entity)
{
	int key = entity->layer;
	auto iter = layers.find(key);
	if (iter == layers.end()) {
		layers[key] = new Layer();
	}
	return layers[key];
}

void World::Recycle()
{
	for (auto layer : layers)
		layer.second->Recycle(this);
}

void World::Instantiation()
{
	for (auto layer : layers)
		layer.second->Instantiation();
}

void World::Physics()
{
	for (auto layer : layers)
		layer.second->Physics(this);
}

void World::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	for (auto layer : layers)
		layer.second->Update(V, P);
}

void World::Render()
{
	for (auto layer : layers)
		layer.second->Render();
}
