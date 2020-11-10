#include "stdafx.h"
#include "AnimRenderer.h"
#include "Transform.h"
#include "World.h"
#include "Renders/AnimationPool.h"

AnimRenderer::AnimRenderer(class Entity* entity):
	Component(entity), anim(nullptr)
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
	anim->Rotation(transform->RotationRad());
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
