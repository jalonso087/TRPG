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
	std::string weaponString;
	std::string typeString;
	bool defeated = false;
	char marker{ ' ' };
	bool runAway;

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
		STICK = 0,
		CLAW,
		HAMMER,
		FANG
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

	~Entity() {}

	void setStartingPosition();
	void setEnemyType(Type& monsterType);
	void typeAsString();
	void move(void);
	bool collision(Entity& player, Entity& ent);
	void encounterHud(Entity& player, Entity& ent);
	void battle(Entity& player, Entity& ent);
	void checkDefeat();
	int damage();
	void weaponAsString();
	void lootGen();
	void attack(Entity& player, Entity& monster);
	void usePotion();
	void exitGame();
	void startMenu();
	void attackLoop(Entity& player, Entity& ent);
	void inn(Entity& player);
	void shop(Entity& player);
	void assignWeapon(int weapon);
	void moveEntity();

};