#pragma once
#include "Entity.h"

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
		weaponAsString();
		typeAsString();
		marker = 'P';
		runAway = false;
	}
};
