#include "stdafx.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"

Entity::Entity()
{
	components.push_back(new Transform(this));
}

Entity::~Entity()
{
	for (auto c : components)
		delete c;
}

void Entity::PhysicsUpdate(World * world)
{
	for (auto c : components)
		c->PhysicsUpdate(world);
}

void Entity::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	for (auto c : components)
		c->Update(V, P);
}

void Entity::Render()
{
	for (auto c : components)
		c->Render();
}

Transform * Entity::GetTransform() const
{
	return (Transform*)components[0];
}
