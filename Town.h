#pragma once
#include "Entity.h"

struct Town : public Entity
{
	Town()
	{
		setStartingPosition();
		type = TOWN;
		maxHP = 255;
		currentHP = maxHP;
		typeAsString();
		marker = 'T';
	}
};