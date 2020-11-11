#include "stdafx.h"
#include "Damager.h"

Damager::Damager(Entity * entity, int hp):
	Component(entity), hp(hp)
{
}

Damager::~Damager()
{
}
