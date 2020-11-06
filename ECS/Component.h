#pragma once
#include "stdafx.h"

class Component {
public:
	Component(class Entity* parent) :parent(parent) {}
	virtual ~Component() {}

	virtual void PhysicsUpdate(class World* world) {}
	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) {}
	virtual void Render() {}

	virtual void UpdateTransform(class Transform* transform) {}
protected:
	class Entity* parent;
};