#pragma once

class World {
public:
	World();
	virtual ~World();

public:
	vector<class Entity*> entity;
	class AnimationPool* pool;

	vector<class Entity*> instantiateBuffer; // Entity here is queued and will be added to entity in next frame...
	vector<class Entity*> trashBuffer; // NOTE THAT ENTITY IN HERE IS ALSO IN ENTITY

};