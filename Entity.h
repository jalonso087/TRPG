#pragma once
#include <string>
#include <conio.h>
#include "Main.h"

struct Entity
{

	int maxHP;
	int currentHP;
	int posX{ 0 };
	int posY{ 0 };
	int type;
	int potions;
	int gold;
	int currentWeapon;
	std::string typeString;
	bool defeated = false;
	char marker{ ' ' };

	enum Type
	{
		PLAYER,
		RAT,
		GOBLIN,
		THIEF,
		WOLF,
		DRAGON,
		TOWN,
		DUNGEON
	};

	enum Weapon
	{
		STICK,
		HAMMER
	};

	enum MovementControls
	{
		KEY_UP = 72,
		KEY_W = 119,
		KEY_LEFT = 75,
		KEY_A = 97,
		KEY_DOWN = 80,
		KEY_S = 115,
		KEY_RIGHT = 77,
		KEY_D = 100,
		KEY_ESC = 27,
		KEY_BACK = 8
	};

	void setStartingPosition();
	void setEnemyType(Type& monsterType);
	void typeAsString();
	void move(void);


};