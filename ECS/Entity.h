#pragma once

class Entity {
public:
	Entity();
	virtual ~Entity();

	virtual void PhysicsUpdate(class World* world);
	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	virtual void Render();

	class Transform* GetTransform() const;

public:
	vector<class Component*> components;
};

