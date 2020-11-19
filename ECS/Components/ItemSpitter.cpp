#include "stdafx.h"
#include "ItemSpitter.h"
#include "ECS/World.h"
#include "ECS/Components/Transform.h"
#include "Prefab/Item/Score.h"

ItemSpitter::ItemSpitter(Entity * entity):
	Component(entity)
{
}

ItemSpitter::~ItemSpitter()
{
	for (auto i : itemPool)
		SAFE_DELETE(i);
}

void ItemSpitter::Recycle(World * world)
{
	for (auto i : itemPool) {
		if (Math::Random(0.0f, 1.0f) < i->prob) {
			int num = Math::Random(i->min, i->max);
			for (int t = 0; t < num; ++t) {
				Entity* temp = nullptr;

				switch (i->ItemCode) {
				case 0x01:
					temp = new Score(world->pool);
					break;
				}

				if (temp) {
					float angle = Math::Random(0.0f, Math::PI*2);
					temp->GetTransform()->Velocity(D3DXVECTOR2(sin(angle), cos(angle))*200.0f);
					temp->GetTransform()->Position(parent->GetTransform()->Position());
					world->GetLayer(temp)->entity.push_back(temp);
				}
			}
		}
	}
}

void ItemSpitter::AddItemPool(ItemPool * item)
{
	itemPool.push_back(item);
}
