#include <string>
#include <conio.h>
#include <vector>
#include <stdlib.h>
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

//function usePotion 
void Entity::usePotion()
{
	potions -= 1;
	system("CLS");  
	std::cout << "You used 1 potion and fully healed." << std::endl;
	currentHP = maxHP;
	 
	std::cin.get();
	system("CLS");
}

void Entity::exitGame()
{
	char exitChoice;
	system("CLS");
	std::cout << "Are you sure you want to exit? (y/n)" << std::endl;
	std::cin >> exitChoice;
	if (exitChoice == 'y') { exit(EXIT_SUCCESS); }
	system("CLS");
}


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
			usePotion();
		}
		break;
	}
	case(KEY_ESC):
	{
		exitGame();
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

		std::cin.get();
		encounterHud(player, ent);
		while (player.defeated == false && ent.defeated == false && player.runAway == false)
		{
			encounterHud(player, ent);
			battle(player, ent);
		}
		if (ent.defeated == true)
		{
			player.lootGen();
		}
		system("CLS");
		//test 3
		player.runAway = false;
		return true;
	}
}

void Entity::encounterHud(Entity& player, Entity& ent)
{
		system("CLS");
		std::cout << player << std::endl;
		std::cout << ent;
		//battle(player, ent);
		if (ent.typeString == "TOWN")
		{
			std::cout << "1. Inn" << std::endl;
			std::cout << "2. Shop" << std::endl;
			std::cout << "3. Leave" << std::endl;
		} 
		else 
		{
			std::cout << "1. Attack" << std::endl;
			std::cout << "2. Heal" << std::endl;
			std::cout << "3. Run" << std::endl;
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
	system("CLS");
	int goldAmount = random_num(1, 30);
	std::cout << "You got " << goldAmount << "gold." << std::endl;
	gold += goldAmount;
	
	maxHP += 5;

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
	std::cin.get();
}
//checkDefeat of entity. 
void Entity::checkDefeat()
{
	if (currentHP <= 0)
	{
		defeated = true;
		system("CLS");
		if (typeString != "PLAYER")
		{
			std::cout << "You defeated " << typeString;
			std::cin.get();
			posX = -1;
			posY = -1;
		}
		else
		{
			std::cout << "You were defeated.";
			std::cin.get();
			exit(EXIT_SUCCESS);
		}
	}
}

void Entity::attack(Entity& ent1, Entity& ent2)
{
	int dmg = ent1.damage();
		
	std::cout << ent1.typeString << " hit " << ent2.typeString << " with " << ent1.weaponString << " for " << dmg << " damage!";

	std::cin.ignore();
	std::cin.get();
	
	ent2.currentHP -= dmg;
	
	ent2.checkDefeat();
}

void Entity::attackLoop(Entity& player, Entity& ent)
{
	player.attack(player, ent);
	encounterHud(player, ent);
	if (!ent.defeated)
		ent.attack(ent, player);
}

void Entity::inn(Entity& player)
{
	system("CLS");
	std::cout << "You rest and heal to full health" << std::endl;
	player.currentHP = player.maxHP;
	std::cin.ignore();
	std::cin.get();
}

void Entity::assignWeapon(int weapon)
{
	currentWeapon = weapon;
	weaponAsString();
}

void Entity::shop(Entity& player)
{
	int shopChoice;
	std::cout << "1. 5 potions - 10g" << std::endl;
	std::cout << "2. Hammer - 30g" << std::endl;
	std::cout << "Selection: " << std::endl;
	std::cin >> shopChoice;
	switch (shopChoice)
	{
		case(1):
		{
			if (player.gold >= 10)
			{
				system("CLS");
				std::cout << "You bought 5 potions.";
				std::cin.ignore();
				std::cin.get();
				player.potions += 5;
			}
			else
			{
				system("CLS");
				std::cout << "You do not have enough gold." << std::endl;
				std::cin.ignore();
				std::cin.get();
			}
		}
		break;
		case(2):
		{
			if (player.gold >= 30)
			{
				system("CLS");
				std::cout << "You bought and equipped a hammer.";
				std::cin.ignore();
				std::cin.get();
				player.assignWeapon(HAMMER);
			}
			else
			{
				system("CLS"); 
				std::cout << "You do not have enough gold." << std::endl;
				std::cin.ignore();
				std::cin.get();
			}
		}
		break;
		case(3):
		{
			player.moveEntity();
			break;
		}
	}
}

void Entity::moveEntity()
{
	posX += 1;
}

//implement battle options function to handle choosing between attack/heal/run
void Entity::battle(Entity& player, Entity& ent)
{
	int battleChoice;

	//encounterHud(player, ent);
	std::cout << "Selection: ";
	std::cin >> battleChoice;
	switch (battleChoice)
	{
		//attack
		case(1):
		{
			if (ent.typeString != "TOWN")
			{
				attackLoop(player, ent);
			} 
			else
			{
				inn(player);
			}
		}
		break;
		//heal
		case(2):	
		{
			if (ent.typeString != "TOWN")
			{
				player.usePotion();
				encounterHud(player, ent);
			}
			else
			{
				shop(player);
			}

		}
		break;
		//run
		case(3):
		{
			player.runAway = true;
			player.moveEntity();
			return;
		}
		break;
	}

}

 void Entity::weaponAsString()
{
	switch (currentWeapon)
	{
		case(STICK): weaponString = "STICK"; break;
		case(CLAW): weaponString = "CLAW"; break;
		case(HAMMER): weaponString = "HAMMER"; break;
		case(FANG): weaponString = "FANG"; break;
	}
}

 void Entity::startMenu()
 {
	 int choice;

	 std::cout << "Welcome to <TRPG>" << std::endl;
	 std::cout << "1. Start Game" << std::endl;
	 std::cout << "2. Quit Game" << std::endl;
	 std::cout << "Selection: ";
	 std::cin >> choice;

	 if (choice == 2)
	 {
		 exitGame();
	 }
 }