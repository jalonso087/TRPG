#pragma once
#include "Entity.h"


struct Goblin : public Entity
{
	Goblin()
	{
		setStartingPosition();
		type = GOBLIN;
		maxHP = (type * 2) + 5;
		currentHP = maxHP;
		typeAsString();
		marker = 'G';
	}
};