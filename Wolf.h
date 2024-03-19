#pragma once
#include "Entity.h"

struct Wolf : public Entity
{
	Wolf()
	{
		setStartingPosition();
		type = WOLF;
		maxHP = (type * 2) + 5;
		currentHP = maxHP;
		typeAsString();
		marker = 'W';
	}
};