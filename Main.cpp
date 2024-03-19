#include <string>
#include <iostream>
#include <conio.h>
#include "Main.h"



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

		//PROOF THAT COLLISION CHECK AGAINST ALL OBJECTS AT ONCE
		//Turn the below into a function (after the for range loop
		for (auto& e : entities)
		{
			if (entity.collision(player, e))
			{
				system("CLS");
				std::cout << "You ran into " << e.typeString;
				std::cin.ignore();
				system("CLS");
			}
				
			std::cout << entity.collision(player, e);
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