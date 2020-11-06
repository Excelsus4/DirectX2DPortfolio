#pragma once
#include "Component.h"
#include "Renders/Animation.h"

class AnimRenderer : public Component {
public:
	AnimRenderer(class Entity* entity);
	virtual ~AnimRenderer();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;
	virtual void UpdateTransform(class Transform* transform) override;

	virtual Animation* SetAnim(Animation* a);
	virtual void PlayAnim(UINT clip);
private:
	Animation* anim;

};