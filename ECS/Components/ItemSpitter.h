#pragma once
#include "ECS/Component.h"

struct ItemPool {
	int ItemCode;
	float prob;
	int min;
	int max;
};

class ItemSpitter :public Component {
public:
	ItemSpitter(class Entity* entity);
	virtual ~ItemSpitter();

	virtual void Recycle(class World* world) override;

	void AddItemPool(ItemPool* item);

private:
	vector<ItemPool*> itemPool;
};