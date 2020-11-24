#pragma once
#include "ECS/Component.h"

class Transform : public Component{
public:
	Transform(class Entity* entity);
	Transform(class Entity* entity, D3DXVECTOR2 pos);
	virtual ~Transform();

	D3DXVECTOR2 Position() const { return position; }
	void Position(D3DXVECTOR2 vec) { position = vec; }
	void Translate(D3DXVECTOR2 vec) { position += vec; }

	D3DXVECTOR2 Velocity() const { return velocity; }
	void Velocity(D3DXVECTOR2 vec) { velocity = vec; }
	void Accelerate(D3DXVECTOR2 vec) { velocity += vec; }
	void Boost(float rate) { velocity *= rate; }

	D3DXVECTOR2 Acceleration() const { return acceleration; }
	void Acceleration(D3DXVECTOR2 vec) { acceleration = vec; }
	void ConstantForce(D3DXVECTOR2 vec) { acceleration += vec; }

	D3DXVECTOR3 RotationRad() const { return rotation; }
	void RotationRad(D3DXVECTOR3 vec) { rotation = vec; }
	void RotationRadLerp(float zRot, float maxTheta);
	void RotateRad(D3DXVECTOR3 vec) { rotation += vec; }

	D3DXVECTOR2 Scale() const { return scale; }
	void Scale(D3DXVECTOR2 vec) { scale = vec; }

	virtual void PhysicsUpdate(class World* world) override;

public:
	bool wallBounce;
private:
	void Reflect(D3DXVECTOR2 normVec);

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 acceleration;

	D3DXVECTOR3 rotation;
	D3DXVECTOR2 scale;
};