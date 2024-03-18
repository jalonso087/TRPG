#pragma once
#include "Entity.h"

//Ask Nav about this - why is this acting like the Entity struct is not defined?
//Entity struct is defined in Entity.h which is included at the preprocessor level
struct Player : public Entity
{
	Player()
	{
		maxHP = 12;
		currentHP = maxHP;
		type = PLAYER;
		potions = 1;
		gold = 0;
		currentWeapon = STICK;
		typeAsString();
		marker = 'P';
	}
};
