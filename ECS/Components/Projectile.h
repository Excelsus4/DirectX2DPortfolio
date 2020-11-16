#pragma once
#include "ECS/Component.h"

class Projectile : public Component {
public:
	Projectile(class Entity* entity);
	virtual ~Projectile();

	void SetEnemyLayer(int layerIDX);
	void SetDamage(int damage);

	virtual void PhysicsUpdate(class World* world) override;
private:
	vector<int> targetLayer;
	int damage;
};