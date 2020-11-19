#include "stdafx.h"
#include "Transform.h"
#include "ECS/World.h"

Transform::Transform(class Entity* entity) :
	Component(entity), position(0.0f, 0.0f), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f), wallBounce(false)
{
}

Transform::Transform(class Entity* entity, D3DXVECTOR2 pos):
	Component(entity), position(pos), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f), wallBounce(false)
{
}

Transform::~Transform()
{
}

void Transform::PhysicsUpdate(World * world)
{
	velocity += acceleration * Timer->Elapsed();
	position += velocity * Timer->Elapsed();
	if (wallBounce) {
		if (position.x > world->screenSize.right) {
			position.x = world->screenSize.right;
			Reflect(D3DXVECTOR2(-1, 0));
		}else if (position.x < world->screenSize.left) {
			position.x = world->screenSize.left;
			Reflect(D3DXVECTOR2(1, 0));
		}
		if (position.y > world->screenSize.top) {
			position.y = world->screenSize.top;
			Reflect(D3DXVECTOR2(0, -1));
		}
		else if (position.y < world->screenSize.bottom) {
			position.y = world->screenSize.bottom;
			Reflect(D3DXVECTOR2(0, 1));
		}
	}
}

void Transform::Reflect(D3DXVECTOR2 normVec)
{
	velocity = velocity - 2 * D3DXVec2Dot(&velocity, &normVec) * normVec;
}
