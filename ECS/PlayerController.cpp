#include "stdafx.h"
#include "PlayerController.h"
#include "Entity.h"
#include "Transform.h"
#include "Prefab/Hydra.h"
#include "World.h"

PlayerController::PlayerController(Entity * entity):
	Component(entity), speed(100.0f), roll(0.4f), pitch(0.3f)
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::PhysicsUpdate(World * world)
{
	Transform* transform = parent->GetTransform();
	D3DXVECTOR3 rotation = transform->RotationRad();

	if (Key->Press(VK_LEFT)) {
		transform->Translate(D3DXVECTOR2(-1, 0)*speed*Timer->Elapsed());
		rotation.y = roll;
	}
	else if (Key->Press(VK_RIGHT)) {
		transform->Translate(D3DXVECTOR2(1, 0)*speed*Timer->Elapsed());
		rotation.y = -roll;
	}
	else {
		rotation.y = 0.0f;
	}

	if (Key->Press(VK_UP)) {
		transform->Translate(D3DXVECTOR2(0, 1)*speed*Timer->Elapsed());
		rotation.x = pitch;
	}
	else if (Key->Press(VK_DOWN)) {
		transform->Translate(D3DXVECTOR2(0, -1)*speed*Timer->Elapsed());
		rotation.x = -pitch;
	}
	else {
		rotation.x = 0.0f;
	}
	transform->RotationRad(rotation);

	// A Key creates Hellfire
	if (Key->Down(0x41)) {
	}

	// S Key creates Hydra
	if (Key->Down(0x53)) {
		Entity* temp = new Hydra(world->pool);
		world->GetLayer(temp)->instantiateBuffer.push_back(temp);
		temp->GetTransform()->Acceleration(D3DXVECTOR2(0, 300.0f));
		temp->GetTransform()->Position(transform->Position());
	}

	// D Key creates Bullet
	if (Key->Down(0x44)) {
	}
}
