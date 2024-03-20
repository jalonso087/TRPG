#pragma once
#include "Entity.h"

struct Dragon : public Entity
{
	Dragon()
	{
		type = DRAGON;
		maxHP = (type * 2) + 5;
		currentHP = maxHP;
		currentWeapon = FANG;
		weaponAsString();
		typeAsString();
	}
	~Dragon() {}
};