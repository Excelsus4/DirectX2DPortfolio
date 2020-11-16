#include "stdafx.h"
#include "Transform.h"

Transform::Transform(class Entity* entity):
	Component(entity),position(0.0f,0.0f), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f),
	rotation(0.0f,0.0f,0.0f), scale(1.0f,1.0f)
{
}

Transform::Transform(class Entity* entity, D3DXVECTOR2 pos):
	Component(entity), position(pos), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f)
{
}

Transform::~Transform()
{
}

void Transform::PhysicsUpdate(World * world)
{
	velocity += acceleration * Timer->Elapsed();
	position += velocity * Timer->Elapsed();
}
