#include <string>
#include <conio.h>
#include <vector>
#include "Main.h"
#include "Entity.h"

	//function to initialize posX posY using random_num(1, mapX/Y))
void Entity::setStartingPosition()
{
	posX = random_num(1, mapX - 1);
	posY = random_num(1, mapY - 1);
}

//void set  enemy type to determine which kind
void Entity::setEnemyType(Type& monsterType)
{
	type = monsterType;
}

//set type as string for down the line implementations
void Entity::typeAsString()
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
void Entity::move(void)
{
	std::cout << "Use WASD or ARROW KEYS to move." << std::endl << "BACKSPACE to use a potion.\nESC to quit game.";
	//Is there a general rule of thumb for when to keep your code on one line or when to expand to multiple lines
	switch (_getch())
	{
		case(KEY_UP): case(KEY_W):
		{
			if (posX >= 1) posX -= 1; break;
		}
		case(KEY_DOWN): case(KEY_S):
		{
			if (posX <= mapX - 2) posX += 1; break;
		}
		case(KEY_LEFT): case(KEY_A):
		{
			if (posY >= 1) posY -= 1; break;
		}
		case(KEY_RIGHT): case(KEY_D):
		{
			if (posY <= mapY - 2) posY += 1; break;
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

//This is bugged - first instance of a collision is immediately resolving
bool Entity::collision(Entity& player, Entity& ent)
{
	if (player.posX == ent.posX && player.posY == ent.posY)
	{
		system("CLS");
		std::cout << "You ran into " << ent.typeString;
		//std::cin.ignore();
		bool dummy = std::cin.get();
		encounter(player, ent);
		bool dummy2 = std::cin.get();
		system("CLS");
		return true;
	}
}

void Entity::encounter(Entity& player, Entity& ent)
{
	while (player.defeated == false && ent.defeated == false)
	{
		system("CLS");
		std::cout << player << std::endl;
		std::cout << ent;
		battle(player, ent);
	}
	
}

int Entity::damage()
{
	int dmg;
	dmg = random_num(1, (currentWeapon+ 1) * 2);
	return dmg;
}

void Entity::lootGen()
{
	int goldAmount = random_num(1, 30);
	std::cout << "You got " << gold << "gold." << std::endl;
	gold += goldAmount;

	int num = random_num(1, 10);
	if (num > 6)
	{
		std::cout << "You got a hammer!";
		currentWeapon = HAMMER;
		weaponAsString();
	}
	else if (num > 2 && num < 7)
	{
		std::cout << "You got 10 health potions.";
		potions += 10;
	}
}

void Entity::checkDefeat()
{
	if (currentHP <= 0)
	{
		defeated = true;
		system("CLS");
		if (typeString != "PLAYER")
		{
			std::cout << "You defeated " << typeString;
			bool dummy = std::cin.get();
		}
		else
		{
			std::cout << "You were defeated.";
			bool dummy = std::cin.get();
			exit(EXIT_SUCCESS);
		}
	}
}

//implement battle options function to handle choosing between attack/heal/run
void Entity::battle(Entity& player, Entity& ent)
{
	int battleChoice; 
	
	std::cout << "1. Attack" << std::endl;
	std::cout << "2. Heal" << std::endl;
	std::cout << "3. Run" << std::endl;
	std::cout << "Selection: ";
	std::cin >> battleChoice;
	switch (battleChoice)
	{
	case(1):
	{
		int dmg = player.damage();
		std::cout << player.typeString << " hit " << ent.typeString << " for " << dmg << "damage!";
		bool dummy = std::cin.get();
		ent.currentHP -= dmg;
		ent.checkDefeat();
		player.checkDefeat();
		break;
	}
	case(2):
	{
		std::cout << player.typeString << "uses 1 potion to heal to full health.";
		player.potions -= 1;
		player.currentHP = player.maxHP;
		break;
	}
	case(3):
		break;
	}
	
	
}

 void Entity::weaponAsString()
{
	switch (currentWeapon)
	{
		case(STICK): weaponString = "STICK";
		case(CLAW): weaponString = "CLAW";
		case(HAMMER): weaponString = "HAMMER";
		case(FANG): weaponString = "FANG";
	}
}