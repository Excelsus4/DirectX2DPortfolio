#pragma once
#include "Animation.h"

class AnimationPool {
public:
	AnimationPool();
	virtual ~AnimationPool();

private:
	void Initialize();
	void InitializeAnim(string key, size_t amount);

public:
	Animation* GetAnim(string key);
	void Recycle(Animation* trash);

private:
	Animation* CreateAnim(string key);

private:
	map<string, vector<Animation*>*> pool;

};