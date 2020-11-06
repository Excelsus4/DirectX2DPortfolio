#include "stdafx.h"
#include "AnimRenderer.h"

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
