#pragma once

class World {
public:
	World();
	virtual ~World();

public:
	vector<class Entity*> entity;
};