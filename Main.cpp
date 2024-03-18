#include <string>
#include <iostream>
#include <conio.h>
#include "Main.h"

const int mapX = 20;
const int mapY = 20;

int random_num(const int& start, const int& max)
{
	return start + rand() % max;
}

void gotoxy(short x, short y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };

	SetConsoleCursorPosition(hStdout, position);
}

std::ostream& operator<<(std::ostream& os, Player character)
{
	os << character.typeString << std::endl
		<< "HP: " << character.currentHP << "/" << character.maxHP << std::endl
		<< "Gold: " << character.gold << "g" << std::endl;
	return os;
}

struct Rat : public Entity
{
	Rat()
	{
		setStartingPosition();
		type = RAT;
		maxHP = (type * 2) + 5;
		currentHP = maxHP;
		typeAsString();
		marker = 'R';
	}
};

struct Goblin : public Entity
{
	Goblin()
	{
		setStartingPosition();
		type = GOBLIN;
		maxHP = (type * 2) + 5;
		currentHP = maxHP;
		typeAsString();
		marker = 'G';
	}
};

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


struct Dragon : public Entity
{
	Dragon()
	{
		type = DRAGON;
		maxHP = (type * 2) + 5;
		currentHP = maxHP;
		typeAsString();
	}
};

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

struct Dungeon : public Entity
{
	Dungeon()
	{
		setStartingPosition();
		type = DUNGEON;
		maxHP = 255;
		currentHP = maxHP;
		typeAsString();
		marker = 'D';
	}
};
/*
void entityVector()
{
	std::vector<Entity> entities;
	entities.push_back(player);
	entities.push_back(rat);
	entities.push_back(goblin);
	entities.push_back(thief);
	entities.push_back(wolf);
	entities.push_back(town);
	entities.push_back(dungeon);
}
*/

void gameLoop()
{
	char Map[mapX][mapY];

	Entity	entity;
	Player	player;
	Rat		rat;
	Goblin	goblin;
	Thief	thief;
	Wolf	wolf;
	Dragon	dragon;
	Town	town;
	Dungeon dungeon;

	std::vector<Entity> entities;

	while (player.defeated == false)
	{
		entities.push_back(player);
		entities.push_back(rat);
		entities.push_back(goblin);
		entities.push_back(thief);
		entities.push_back(wolf);
		entities.push_back(town);
		entities.push_back(dungeon);

		std::cout << player;

		//Could not find a way to fill the 2d array with < O(n^2) complexity
		for (int i = 0; i < mapX; i++)
		{
			for (int j = 0; j < mapY; j++)
			{
				Map[i][j] = '.';

				for (const auto& e : entities)
				{
					Map[e.posX][e.posY] = e.marker;
				}

				std::cout << Map[i][j];

			}
			std::cout << std::endl;
		}
		player.move();
		gotoxy(0, 0);
		//player entity was not updating position in real time, so clearing and pushing contents again will update all entities position as in real time
		entities.clear();
	}
}

int main()
{
	srand(NULL);

	gameLoop();
	return 0;
}