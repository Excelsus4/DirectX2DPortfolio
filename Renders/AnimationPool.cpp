#include "stdafx.h"
#include "AnimationPool.h"

AnimationPool::AnimationPool()
{
	Initialize();
}

AnimationPool::~AnimationPool()
{
	for each (pair<string,vector<Animation*>*> p in pool)
	{
		for each (Animation* anim in *p.second)
		{
			SAFE_DELETE(anim);
		}
		SAFE_DELETE(p.second);
	}
}

void AnimationPool::Initialize()
{
	InitializeAnim("Apache_Body", 1);
	InitializeAnim("Apache_Rotor", 1);
	InitializeAnim("Apache_Rotor_FX", 1);

	InitializeAnim("Missile_Hydra", 16);
	InitializeAnim("Missile_Hellfire", 4);
}

void AnimationPool::InitializeAnim(string key, size_t amount)
{
	pool[key] = new vector<Animation*>();
	for(size_t i =0; i < amount; ++i)
		Recycle(CreateAnim(key));
}

Animation * AnimationPool::GetAnim(string key)
{
	Animation* anim;
	if (pool[key]->size() > 0) {
		anim = pool[key]->back();
		pool[key]->pop_back();
	}
	else {
		anim = CreateAnim(key);
	}
	return anim;
}

void AnimationPool::Recycle(Animation * trash)
{
	pool[trash->key]->push_back(trash);
}

Animation * AnimationPool::CreateAnim(string key)
{
	Animation* anim = nullptr;
	if (key == "Apache_Body") {
		anim = new Animation();
		anim->key = key;

		wstring spriteFile = Textures + L"Helicopter_64.png";
		wstring shaderFile = Shaders + L"009_Sprite.fx";

		{
			Clip* clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 0, 64, 64), 0.2f);
			anim->AddClip(clip);
		}
	}
	else if (key == "Apache_Rotor") {
		anim = new Animation();
		anim->key = key;

		wstring spriteFile = Textures + L"Helicopter_64.png";
		wstring shaderFile = Shaders + L"009_Sprite.fx";

		{
			Clip* clip = new Clip(PlayMode::Loop);
			for (int i = 9; i >= 0; --i) {
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 
					i * 64.0f, 64.0f, i*64.0f+64.0f, 128.0f
				), 0.05f);
			}
			anim->AddClip(clip);
		}
	}
	else if (key == "Apache_Rotor_FX") {
		anim = new Animation();
		anim->key = key;

		wstring spriteFile = Textures + L"Helicopter_64.png";
		wstring shaderFile = Shaders + L"009_Sprite.fx";

		{
			Clip* clip = new Clip(PlayMode::Loop);
			for (int i = 0; i < 8; ++i) {
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 
					i * 64.0f, 128.0f, i * 64.0f + 64.0f, 192.0f
				), 0.1f);
			}
			anim->AddClip(clip);
		}
	}
	else if (key == "Missile_Hydra") {
		anim = new Animation();
		anim->key = key;

		wstring spriteFile = Textures + L"Missile_64.png";
		wstring shaderFile = Shaders + L"009_Sprite.fx";

		{
			Clip* clip = new Clip(PlayMode::Loop);
			for (int i = 0; i < 2; ++i) {
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 
					192.0f, i * 64.0f, 256.0f, i * 64.0f + 64.0f
				), 0.1f);
			}
			anim->AddClip(clip);
		}
	}
	else if (key == "Missile_Hellfire") {
		anim = new Animation();
		anim->key = key;

		wstring spriteFile = Textures + L"Missile_64.png";
		wstring shaderFile = Shaders + L"009_Sprite.fx";

		{
			Clip* clip = new Clip(PlayMode::End);
			for (int i = 0; i < 2; ++i) {
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 
					384.0f, i * 64.0f, 448.0f, i * 64.0f + 64.0f
				), 0.3f);
			}
			anim->AddClip(clip);
		}
	}

	return anim;
}
