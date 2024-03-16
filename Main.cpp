#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <conio.h>
#include <Windows.h>

const static int mapX = 20;
const static int mapY = 20;

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

	//enum to declare different types
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

	//function to initialize posX posY using random_num(1, mapX/Y))
	void setStartingPosition()
	{
		posX = random_num(1, mapX-1);
		posY = random_num(1, mapY-1);
	}

	//void set  enemy type to determine which kind
	void setEnemyType(Type& monsterType)
	{
		type = monsterType;
	}

	//set type as string for down the line implementations
	void typeAsString()
	{
		switch (type)
		{
		case(PLAYER): { typeString = "PLAYER"; break; }
		case(RAT): { typeString = "RAT"; break; }
		case(GOBLIN): { typeString = "GOBLIN"; break; }
		case(THIEF): { typeString = "THIEF"; break; }
		case(WOLF): { typeString = "WOLF"; break; }
		case(DRAGON): { typeString = "DRAGON"; break; }
		case(TOWN): { typeString = "TOWN"; break; }
		case(DUNGEON): { typeString = "DUNGEON"; break; }
		}
	}

	//Create Map hud for player data possibly using << overload

	//function for movement to track increment/decrement to posX and posY
	void move(void)
	{
		std::cout << "Use WASD or ARROW KEYS to move." << std::endl << "BACKSPACE to use a potion.\nESC to quit game.";
		//Is there a general rule of thumb for when to keep your code on one line or when to expand to multiple lines
		switch (_getch())
		{
		case(KEY_UP): case(KEY_W): 
		{ 
			if(posX >= 1) posX -= 1; break; 
		}
		case(KEY_DOWN): case(KEY_S): 
		{ 
			if(posX <= mapX-2 ) posX += 1; break; 
		}
		case(KEY_LEFT): case(KEY_A): 
		{
			if(posY >= 1) posY -= 1; break; 
		}
		case(KEY_RIGHT): case(KEY_D): 
		{ 
			if(posY <= mapY-2) posY += 1; break; 
		}
		case(KEY_BACK): 
			{ 
				if (potions > 0) 
				{ 
					potions -= 1; 
					system("CLS");  std::cout << "You used 1 potion and fully healed." << std::endl;
					currentHP = maxHP;
					std::cin.ignore(); system("CLS");
				}
				break;
			}
		case(KEY_ESC): 
			{
				char exitChoice;
				system("CLS");
				std::cout << "Are you sure you would like to exit? (y/n)" << std::endl;
				std::cin >> exitChoice;
				if (exitChoice == 'y') { exit(EXIT_SUCCESS); }
				system("CLS");
				break;
			}
		}
	}
};

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
void mapDisplay()
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

	mapDisplay();
	return 0;
}