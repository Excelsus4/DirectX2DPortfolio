#pragma once
#include "Component.h"

class Projectile : public Component {
public:
	Projectile(class Entity* entity);
	virtual ~Projectile();

	void SetEnemyLayer(int layerIDX);

	virtual void PhysicsUpdate(class World* world) override;
private:
	vector<int> targetLayer;
};