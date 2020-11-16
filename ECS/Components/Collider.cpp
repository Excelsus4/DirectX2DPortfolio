#include "stdafx.h"
#include "Collider.h"
#include "Transform.h"

Collider::Collider(Entity * entity, D3DXVECTOR2 size):
	Component(entity), size(size)
{
	// Initialize Bound Shader
	bDrawBound = false;
	boundShader = new Shader(Shaders + L"015_Bounding.fx");

	// Create Bound Vertex Buffer
	BoundVertex vertices[5];

	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);

	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(BoundVertex) * 5;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &boundVertexBuffer);
		assert(SUCCEEDED(hr));
	}
}

Collider::~Collider()
{
	SAFE_DELETE(boundShader);
	SAFE_RELEASE(boundVertexBuffer);
}

void Collider::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	boundShader->AsMatrix("View")->SetMatrix(V);
	boundShader->AsMatrix("Projection")->SetMatrix(P);

	D3DXMATRIX S, R, T;
	D3DXMatrixScaling(&S, scale.x * size.x, scale.y * size.y, 1.0f);
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&T, floorf(position.x) + 0.5f + scale.x * 0.5f, floorf(position.y) + 0.5f + scale.y*0.5f, 0.0f);
	world = S * R * T;

	boundShader->AsMatrix("World")->SetMatrix(world);
}

void Collider::Render()
{
	if (bDrawBound == true) {
		UINT stride = sizeof(BoundVertex);
		UINT offset = 0;

		DeviceContext->IASetVertexBuffers(0, 1, &boundVertexBuffer, &stride, &offset);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		boundShader->Draw(0, 0, 5);
	}
}

void Collider::UpdateTransform(Transform * transform)
{
	position = transform->Position();
	rotation = transform->RotationRad();
	scale = transform->Scale();
}

bool Collider::AABB(D3DXVECTOR2 & position)
{
	return AABB(this, position);
}

bool Collider::AABB(Collider * b)
{
	return AABB(this, b);
}

bool Collider::Obb(Collider * b)
{
	return Obb(this, b);
}

bool Collider::AABB(Collider * a, D3DXVECTOR2 & position)
{
	float xScale = a->scale.x * a->size.x * 0.5f;
	float yScale = a->scale.y * a->size.y * 0.5f;

	float left = a->position.x - xScale;
	float right = a->position.x + xScale;
	float bottom = a->position.y - yScale;
	float top = a->position.y + yScale;

	bool b = true;
	b &= position.x > left;
	b &= position.x <= right;
	b &= position.y > bottom;
	b &= position.y <= top;

	return b;
}

bool Collider::AABB(Collider * a, Collider * b)
{
	float xScale = a->scale.x * a->size.x * 0.5f;
	float yScale = a->scale.y * a->size.y * 0.5f;

	float leftA = a->position.x - xScale;
	float rightA = a->position.x + xScale;
	float bottomA = a->position.y - yScale;
	float topA = a->position.y + yScale;

	xScale = b->scale.x * b->size.x * 0.5f;
	yScale = b->scale.y * b->size.y * 0.5f;

	float leftB = b->position.x - xScale;
	float rightB = b->position.x + xScale;
	float bottomB = b->position.y - yScale;
	float topB = b->position.y + yScale;

	bool bCheck = true;
	bCheck &= leftA < rightB;
	bCheck &= topA > bottomB;
	bCheck &= rightA > leftB;
	bCheck &= bottomA < topB;

	return bCheck;
}

bool Collider::Obb(Collider * a, Collider * b)
{
	ObbDesc obbA, obbB;

	D3DXVECTOR2 lengthA = D3DXVECTOR2(a->world._11, a->world._22) * 0.5f;
	CreateObb(&obbA, a->position, a->world, lengthA);
	D3DXVECTOR2 lengthB = D3DXVECTOR2(b->world._11, b->world._22) * 0.5f;
	CreateObb(&obbB, b->position, b->world, lengthB);

	return CheckObb(obbA, obbB);
}

void Collider::CreateObb(OUT ObbDesc * out, D3DXVECTOR2 & pos, D3DXMATRIX & world, D3DXVECTOR2 & length)
{
	out->Position = pos;

	out->Length[0] = length.x;
	out->Length[1] = length.y;
	out->Direction[0] = D3DXVECTOR2(world._11, world._12);
	out->Direction[1] = D3DXVECTOR2(world._21, world._22);

	D3DXVec2Normalize(&out->Direction[0], &out->Direction[0]);
	D3DXVec2Normalize(&out->Direction[1], &out->Direction[1]);
}

float Collider::SeparateAxis(D3DXVECTOR2 & separate, D3DXVECTOR2 & e1, D3DXVECTOR2 & e2)
{
	float r1 = fabsf(D3DXVec2Dot(&separate, &e1));
	float r2 = fabsf(D3DXVec2Dot(&separate, &e2));

	return r1 + r2;
}

bool Collider::CheckObb(ObbDesc & obbA, ObbDesc & obbB)
{
	D3DXVECTOR2 nea1 = obbA.Direction[0], ea1 = nea1 * obbA.Length[0];
	D3DXVECTOR2 nea2 = obbA.Direction[1], ea2 = nea2 * obbA.Length[1];
	D3DXVECTOR2 neb1 = obbB.Direction[0], eb1 = neb1 * obbB.Length[0];
	D3DXVECTOR2 neb2 = obbB.Direction[1], eb2 = neb2 * obbB.Length[1];
	D3DXVECTOR2 direction = obbA.Position - obbB.Position;


	float lengthA = 0.0f, lengthB = 0.0f, length = 0.0f;

	lengthA = D3DXVec2Length(&ea1);
	lengthB = SeparateAxis(nea1, eb1, eb2);
	length = fabsf(D3DXVec2Dot(&direction, &nea1));
	if (length > lengthA + lengthB)
		return false;

	lengthA = D3DXVec2Length(&ea2);
	lengthB = SeparateAxis(nea2, eb1, eb2);
	length = fabsf(D3DXVec2Dot(&direction, &nea2));
	if (length > lengthA + lengthB)
		return false;


	lengthA = SeparateAxis(neb1, ea1, ea2);
	lengthB = D3DXVec2Length(&eb1);
	length = fabsf(D3DXVec2Dot(&direction, &neb1));
	if (length > lengthA + lengthB)
		return false;

	lengthA = SeparateAxis(neb2, ea1, ea2);
	lengthB = D3DXVec2Length(&eb2);
	length = fabsf(D3DXVec2Dot(&direction, &neb2));
	if (length > lengthA + lengthB)
		return false;

	return true;
}
