#pragma once
#include "Animation.h"

struct InitSchedule {
	string key;
	int amount;
};

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

public:
	bool Process();
	void Render();

private:
	int animas[2];
	int current;
	vector<InitSchedule*> schedule;
};