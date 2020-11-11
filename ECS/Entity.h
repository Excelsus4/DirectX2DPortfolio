#pragma once

class Entity {
public:
	Entity(int layer);
	virtual ~Entity();

	virtual void PhysicsUpdate(class World* world);
	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	virtual void Render();
	virtual void Recycle(class World* world);

	class Transform* GetTransform() const;

public:
	int layer;
	vector<class Component*> components;
};

