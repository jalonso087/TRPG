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
		currentWeapon = CLAW;
		weaponAsString();
		typeAsString();
		marker = 'H';
	}
	~Thief() {}
};