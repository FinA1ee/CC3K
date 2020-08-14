#ifndef FLOOR_H
#define FLOOR_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "cell.h"
#include "item.h"
#include "gold.h"
#include "hero.h"
#include "enemy.h"
class Merchant;
class Floor {
	Hero* h = nullptr;
	Cell* heroCell = nullptr;
	int heroRow = -1;
	int heroCol = -1;
	int heroChamber = -1;
	int levelNum = 1;
	
	bool pickGold = false;
	bool enemyFroze = false;
	bool attackMode = false;
	bool combatAction = false;
	bool isMerchantBad = false;
	
	std::string action = "";
	std::vector<std::vector<Cell *>>floorInfo;
	std::vector<std::vector<Cell *>>chamber;
	std::vector<Cell *>enemyInfo;

    void initChamber();
	
	void generateHero();

	void generateStair();

	void generatePotion();

	void generateGold();

	bool generateDragon(Gold *, Cell *, int);

	void generateEnemy();		

	void heroPickGold(Cell *);

	void enemyMove();

	void printHeroInfo();
	
	public:
		~Floor();
		
		void generateAll();

		void setHero(Hero *);
		
		void readFloor(std::ifstream&, int);
		
		void heroTakePotion(std::string dir);

		void heroMove(std::string dir, bool usePotion);
		
		void heroAttack(std::string dir);
		
		void checkAround();
		
		void frozeEnemy();
		
		bool reachStair();
		
		void displayScore() const;

		void printFloor();

		void clearBoard();
};


#endif








