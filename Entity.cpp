#include <string>
#include <conio.h>
#include <vector>
#include "Main.h"
#include "Entity.h"

Entity entity;

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

bool Entity::collision(Entity& player, Entity &monster)
{
	if (monster.posX == player.posX && monster.posY == player.posY)
		return true;
	else
		return false;
}
