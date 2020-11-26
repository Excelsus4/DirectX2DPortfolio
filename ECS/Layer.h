#pragma once

class Layer {
public:
	static int GetLayerIDX(string name);
public:
	void ClearLayer(class World* world);
	void Recycle(class World* world);
	void Instantiation();
	void Physics(class World* world);
	void Update(D3DXMATRIX & V, D3DXMATRIX & P);
	void Render();

public:
	vector<class Entity*> entity;
	vector<class Entity*> instantiateBuffer; // Entity here is queued and will be added to entity in next frame...
	vector<class Entity*> trashBuffer; // NOTE THAT ENTITY IN HERE IS ALSO IN ENTITY
};