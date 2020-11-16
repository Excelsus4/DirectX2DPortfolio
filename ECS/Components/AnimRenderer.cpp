#include "stdafx.h"
#include "AnimRenderer.h"
#include "Transform.h"
#include "ECS/World.h"
#include "Renders/AnimationPool.h"

AnimRenderer::AnimRenderer(class Entity* entity):
	Component(entity), anim(nullptr), isRotationSpriteBased(false)
{
}

AnimRenderer::~AnimRenderer()
{
}

void AnimRenderer::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	anim->Update(V, P);
}

void AnimRenderer::Render()
{
	anim->Render();
}

void AnimRenderer::Recycle(World * world)
{
	world->pool->Recycle(anim);
}

void AnimRenderer::UpdateTransform(Transform * transform)
{
	anim->Position(transform->Position());
	if (!isRotationSpriteBased)
		anim->Rotation(transform->RotationRad());
	else {
		anim->Rotation(0, 0, 0);
		float rot = -transform->RotationRad().z; // 0~2pi
		rot /= Math::PI*2;						//TODO: Remove pi with a magic number... it becomes 0~1
		rot *= rotationSpriteSize;				// 0~16
		anim->Play((UINT)(((int)rot + rotationSpriteSize * 128) % rotationSpriteSize));
	}
	anim->Scale(transform->Scale());
}

Animation* AnimRenderer::SetAnim(Animation* a)
{
	Animation* ret = anim;
	anim = a;
	return ret;
}

void AnimRenderer::PlayAnim(UINT clip)
{
	anim->Play(clip);
}
