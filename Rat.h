#pragma once
#include "Entity.h"

struct Rat : public Entity
{
	Rat()
	{
		setStartingPosition();
		type = RAT;
		maxHP = (type * 2) + 5;
		currentHP = maxHP;
		currentWeapon = CLAW;
		weaponAsString();
		typeAsString();
		marker = 'R';
	}
	~Rat() {}
};
