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
	return GetLayer(entity->layer);
}

Layer * World::GetLayer(int layerIDX)
{
	auto iter = layers.find(layerIDX);
	if (iter == layers.end()) {
		layers[layerIDX] = new Layer();
	}
	return layers[layerIDX];
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
