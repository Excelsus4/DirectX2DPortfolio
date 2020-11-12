#pragma once
#include "Component.h"

class Collider : public Component {
public:
	Collider(class Entity* entity, D3DXVECTOR2 size);
	virtual ~Collider();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;
	virtual void UpdateTransform(class Transform* transform) override;

	void DrawBound(bool val) { bDrawBound = val; }

public:
	//=========================================================================
	// Collision Check
	bool AABB(D3DXVECTOR2& position);
	bool AABB(Collider* b);
	bool Obb(Collider* b);

	static bool AABB(Collider* a, D3DXVECTOR2& position);
	static bool AABB(Collider* a, Collider* b);
	static bool Obb(Collider* a, Collider* b);

private:
	struct ObbDesc {
		D3DXVECTOR2 Position;
		D3DXVECTOR2 Direction[2];
		float Length[2];
	};

	static void CreateObb(OUT ObbDesc* out, D3DXVECTOR2& pos, D3DXMATRIX& world, D3DXVECTOR2& length);
	static float SeparateAxis(D3DXVECTOR2& separate, D3DXVECTOR2& e1, D3DXVECTOR2& e2);
	static bool CheckObb(ObbDesc& obbA, ObbDesc& obbB);

private:
	bool bDrawBound;
	Shader* boundShader;
	ID3D11Buffer* boundVertexBuffer;
	D3DXMATRIX world;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 size;

private:
	struct BoundVertex {
		D3DXVECTOR3 Position;
	};
};