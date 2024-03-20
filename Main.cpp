#include <string>
#include <iostream>
#include <conio.h>
#include "Main.h"

char Map[mapX][mapY];

/*
Entity	entity;
Player	player;
Rat		rat;
Goblin	goblin;
Thief	thief;
Wolf	wolf;
Dragon	dragon;
Town	town;
Dungeon dungeon;
*/

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

std::ostream& operator<<(std::ostream& os, const Entity& ent)
{
	os << ent.typeString << std::endl;

	if (ent.typeString != "DUNGEON" && ent.typeString != "TOWN")
	{
		std::cout << "HP: " << ent.currentHP << "/" << ent.maxHP << std::endl;
	}
	
	if (ent.typeString == "PLAYER")
	{
		std::cout << "Gold: " << ent.gold << "g" << std::endl << "Potions: " << ent.potions << std::endl;
	}

	return os;
}

void startMenu()
{
	int choice; 

	std::cout << "Welcome to <TRPG>" << std::endl;
	std::cout << "1. Start Game" << std::endl; 
	std::cout << "2. Quit Game" << std::endl;
	std::cout << "Selection: ";
	std::cin >> choice;
	if (choice == 2)
		exit(EXIT_SUCCESS);
}

void gameLoop()
{
	std::vector<Entity> entities;

	startMenu();

	Entity	entity;
	Player	player;
	Rat		rat;
	Goblin	goblin;
	Thief	thief;
	Wolf	wolf;
	Dragon	dragon;
	Town	town;
	Dungeon dungeon;

	system("CLS");
	
	while (player.defeated == false)
	{
		entities.push_back(rat);
		entities.push_back(goblin);
		entities.push_back(thief);
		entities.push_back(wolf);
		entities.push_back(town);
		entities.push_back(dungeon);
		entities.push_back(player);
		
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

		//Remove player from the entities vector so it does not collide with itself
		entities.pop_back();

		for (auto& e : entities) 
		{ 
			entity.collision(player, e); 
		}

		gotoxy(0, 0);

		//player entity was not updating position in real time, so clearing and pushing contents again will update all entities position as in real time
		entities.clear();
	}
}

int main()
{
	srand(time(0));

	gameLoop();
	return 0;
}