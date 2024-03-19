#pragma once
#include <random>
#include <Windows.h>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Rat.h"
#include "Goblin.h"
#include "Thief.h"
#include "Wolf.h"
#include "Dragon.h"
#include "Town.h"
#include "Dungeon.h"

const static int mapX = 20;
const static int mapY = 20;

int random_num(const int& start, const int& max);
void gotoxy(short x, short y);
std::ostream& operator<<(std::ostream& os, const Entity& ent);
bool startMenu();
void gameLoop();