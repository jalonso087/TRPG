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


int random_num(const int& start, const int& max);

void gotoxy(short x, short y);

std::ostream& operator<<(std::ostream& os, Player character);

void gameLoop();