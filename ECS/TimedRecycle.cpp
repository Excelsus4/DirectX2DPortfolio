#include "stdafx.h"
#include "TimedRecycle.h"
#include "World.h"

TimedRecycle::TimedRecycle(Entity * entity, float ttl):
	Component(entity), ttl(ttl)
{
	age = 0;
}

TimedRecycle::~TimedRecycle()
{
}

void TimedRecycle::PhysicsUpdate(World * world)
{
	age += Timer->Elapsed();
	if (age >= ttl) {
		world->GetLayer(parent)->trashBuffer.push_back(parent);
	}
}
