#include "stdafx.h"
#include "World.h"
#include "Entity.h"
#include "ECS/Components/Transform.h"

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
	for (auto scl : ScrollLayers) {
		for (auto e : layers[scl]->entity) {
			e->GetTransform()->Translate(D3DXVECTOR2(0, ScrollSpeed * Timer->Elapsed()));
		}
	}

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

Entity * World::GetUserEntity()
{
	// if user exist, return user entity, else, return nullptr
	auto userLayer = GetLayer(Layer::GetLayerIDX("User"));
	if (userLayer->entity.size() > 0)
		return userLayer->entity[0];
	return nullptr;
}
