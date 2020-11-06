#pragma once
#include "Component.h"

class Transform : public Component{
public:
	Transform(class Entity* entity);
	Transform(class Entity* entity, D3DXVECTOR2 pos);
	virtual ~Transform();

	D3DXVECTOR2 Position() const { return position; }
	void Position(D3DXVECTOR2 vec) { position = vec; }
	void Translate(D3DXVECTOR2 vec) { position += vec; }

	D3DXVECTOR3 RotationRad() const { return rotation; }
	void RotationRad(D3DXVECTOR3 vec) { rotation = vec; }
	void RotateRad(D3DXVECTOR3 vec) { rotation += vec; }

	D3DXVECTOR2 Scale() const { return scale; }
	void Scale(D3DXVECTOR2 vec) { scale = vec; }

private:
	D3DXVECTOR2 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 scale;
};