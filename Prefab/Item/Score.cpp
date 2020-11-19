#include "stdafx.h"
#include "Score.h"
#include "ECS/Layer.h"
#include "ECS/Components/AnimRenderer.h"
#include "ECS/Components/Item.h"
#include "ECS/Components/Collider.h"
#include "ECS/Components/Transform.h"

Score::Score(AnimationPool * pool):
	Entity(Layer::GetLayerIDX("Item"))
{
	this->GetTransform()->wallBounce = true;

	AnimRenderer* animRenderer = new AnimRenderer(this);
	animRenderer->SetAnim(pool->GetAnim("Coin"));
	animRenderer->PlayAnim(0);
	components.push_back(animRenderer);

	Item* itemAction = new Item(this, 16000000.0f, 0x8400064);
	components.push_back(itemAction);

	Collider* collider = new Collider(this, D3DXVECTOR2(64, 64));
	components.push_back(collider);
}

Score::~Score()
{
}
