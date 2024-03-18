#pragma once
#include "Entity.h"

struct Thief : public Entity
{
	Thief()
	{
		setStartingPosition();
		type = THIEF;
		maxHP = (type * 2) + 5;
		currentHP = maxHP;
		typeAsString();
		marker = 'H';
	}
};