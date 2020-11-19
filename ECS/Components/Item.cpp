#include "stdafx.h"
#include "Item.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ECS/World.h"
#include "ECS/Components/Collider.h"

Item::Item(Entity * entity, float gravity, int itemCode):
	Component(entity), gravity(gravity), itemCode(itemCode)
{
}

Item::~Item()
{
}

void Item::PhysicsUpdate(World * world)
{
	Transform* transform = parent->GetTransform();
	Entity* user = world->GetUserEntity();
	if (user != nullptr) {
		// Accelerate toward user by gravity formula
		D3DXVECTOR2 delta = user->GetTransform()->Position() - transform->Position();
		float distance = D3DXVec2LengthSq(&delta);
		D3DXVec2Normalize(&delta, &delta);
		delta *= gravity / distance;
		transform->Boost(1 - Timer->Elapsed());
		transform->Accelerate(delta*Timer->Elapsed());

		// Collide with user and feed...
		if (((Collider*)parent->GetComponent(typeid(Collider).name()))->AABB(user->GetTransform()->Position())) {
			user->SpecialScript(world, itemCode);
			world->GetLayer(parent)->trashBuffer.push_back(parent);
		}
	}
}
