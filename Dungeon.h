#pragma once
#include "Entity.h"

struct Dungeon : public Entity
{
	Dungeon()
	{
		setStartingPosition();
		type = DUNGEON;
		maxHP = 255;
		currentHP = maxHP;
		typeAsString();
		marker = 'D';
	}
};
