#include "stdafx.h"
#include "PlayerController.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "Prefab/Hydra.h"
#include "ECS/World.h"

PlayerController::PlayerController(Entity * entity):
	Component(entity), speed(200.0f), roll(0.4f), pitch(0.3f),
	attackspeed(0.05f), cooltime(0.0f)
{
	ammo[0] = 8;
	ammo[1] = 60;
	ammo[2] = 1000;
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
		//rotation.y = roll;
	}
	else if (Key->Press(VK_RIGHT)) {
		transform->Translate(D3DXVECTOR2(1, 0)*speed*Timer->Elapsed());
		//rotation.y = -roll;
	}
	else {
		//rotation.y = 0.0f;
	}

	if (Key->Press(VK_UP)) {
		transform->Translate(D3DXVECTOR2(0, 1)*speed*Timer->Elapsed());
		//rotation.x = pitch;
	}
	else if (Key->Press(VK_DOWN)) {
		transform->Translate(D3DXVECTOR2(0, -1)*speed*Timer->Elapsed());
		//rotation.x = -pitch;
	}
	else {
		//rotation.x = 0.0f;
	}
	transform->RotationRad(rotation);

	// A Key creates Hellfire
	if (Key->Down(0x41)) {
		if (ammo[0] > 0) {
			--ammo[0];
			parent->SpecialScript(world, 0x0100041);
		}
	}

	// S Key creates Hydra
	if (Key->Down(0x53)) {
		if (ammo[1] > 0) {
			--ammo[1];
			parent->SpecialScript(world, 0x0100053);
		}
	}

	cooltime -= Timer->Elapsed();
	// D Key creates Bullet
	if (Key->Press(0x44)) {
		if (cooltime < 0 && ammo[2] > 0) {
			--ammo[2];
			cooltime = attackspeed;
			parent->SpecialScript(world, 0x0100044);
		}
	}
}

void PlayerController::ImGuiDisplayAmmo()
{
	ImGui::LabelText("Hellfires", "%d", ammo[0]);
	ImGui::LabelText("Hydras", "%d", ammo[1]);
	ImGui::LabelText("Guns", "%d", ammo[2]);
}
