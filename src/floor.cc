#include "cell.h"
#include "floor.h"
#include "potion.h"
#include "item.h"
#include "gold.h"
#include "enemy.h"
#include "human.h"
#include "dragon.h"
#include "elf.h"
#include "orc.h"
#include "dwarf.h"
#include "halfling.h"
#include "merchant.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <iomanip>
using namespace std;

		
	void Floor::setHero(Hero *h){this->h = h;} // Set hero pointer
	
	Floor::~Floor(){} 
					
	void Floor::initChamber(){
	// Initialize all chambers, eatablish observer and subject pattern
		vector<Cell *>chamOne;
		vector<Cell *>chamTwo;
		vector<Cell *>chamThree;
		vector<Cell *>chamFour;	
		vector<Cell *>chamFive;
		for(int i = 0; i < 25 ; i++) {
			for(int j = 0; j < 79; j++) {
				char x = floorInfo[i][j]->getCellChar();
				if (x == '.') {
					if (j <= 28 && j >= 3 && i <= 6 && i >= 3){
						chamOne.emplace_back(floorInfo[i][j]);
					}
					else if (j <= 49 && j >= 37 && i <= 12 && i >= 10){
						chamTwo.emplace_back(floorInfo[i][j]);
					}
					else if (j <= 25 && j >= 4 && i <= 21 && i >= 15){
						chamThree.emplace_back(floorInfo[i][j]);
					}
					else if (j <= 75 && j >= 37 && i <= 21 && i >= 16){
						chamFour.emplace_back(floorInfo[i][j]);
					}
					else {
						chamFive.emplace_back(floorInfo[i][j]);
					}
				}
			}	
		}
		chamber.emplace_back(chamOne);
		chamber.emplace_back(chamTwo);
		chamber.emplace_back(chamThree);
		chamber.emplace_back(chamFour);
		chamber.emplace_back(chamFive);
		for(int i = 0; i < 25; i++) {
			for(int j = 0; j < 79; j++) { 
				if((i-1) >= 0) floorInfo[i][j]->attach(floorInfo[i-1][j]);
				if((i+1) < 25) floorInfo[i][j]->attach(floorInfo[i+1][j]);
				if((j-1) >= 0) floorInfo[i][j]->attach(floorInfo[i][j-1]);
				if((j+1) < 79) floorInfo[i][j]->attach(floorInfo[i][j+1]);
				if((i-1) >= 0 && (j-1)>=0) floorInfo[i][j]->attach(floorInfo[i-1][j-1]);
				if((i+1) < 25 && (j-1)>=0) floorInfo[i][j]->attach(floorInfo[i+1][j-1]);
				if((i-1) >= 0 && (j+1)< 79) floorInfo[i][j]->attach(floorInfo[i-1][j+1]);
				if((i+1) < 25 && (j+1)< 79) floorInfo[i][j]->attach(floorInfo[i+1][j+1]);
			}
		}	
	}	
	
	
	void Floor::readFloor(ifstream& inputFile, int level){
	// Read in floor file, create a 2d vector of Cell pointers
	//  If a floor display is given, transform numbers and generate items
	//  and enemies.
		char x;
		string line;
		floorInfo.clear();
		enemyInfo.clear();
		chamber.clear();
		for(int a = 0; a < 25*(level-1); a++){getline(inputFile, line);}
		for(int i=0; i<25; i++){
			vector<Cell *> row;
			getline(inputFile, line);
			for(int j=0; j<79; j++){
				x = line[j];
				Cell *c = new Cell{i,j,x};
				row.emplace_back(c);
			}
			floorInfo.emplace_back(row);
		}
		initChamber();
	    for(int i=0; i<25; i++){
			for(int j=0; j<79; j++){
				char c = floorInfo[i][j]->getCellChar();
				if(c == '@'){
					heroCell = floorInfo[i][j];
					heroRow = i;
					heroCol = j;
					if (levelNum == 1){action = "Player Character Has Spawned.";}
					else {action = "PC Enters Next Floor";}
				}
				if(c == '\\'){
					floorInfo[i][j]->setStair();
				}
				if(c >= '0' && c <= '5'){
					int pType = c-'0'+1;
					Potion *p = new Potion{pType};
					floorInfo[i][j]->setItem(p);
				}
				if(c == '6'){
					Gold *g = new Gold{8};
					floorInfo[i][j]->setItem(g);
				}
				if(c == '7'){
					Gold *g = new Gold{1};
					floorInfo[i][j]->setItem(g);
				}
				if(c == '8'){
					Gold *g = new Gold{10};
					floorInfo[i][j]->setItem(g);
				}
				if(c == '9'){
					Gold *g = new Gold{3};
					floorInfo[i][j]->setItem(g);
					for(int a=i-1; a<i+1; a++){
						for(int b=j-1; b<j+1; b++){
							if(floorInfo[a][b]->getCellChar() == 'D'){
								Enemy *e = new Dragon{g};
								floorInfo[i][j]->setEnemy(e);
								enemyInfo.emplace_back(floorInfo[i][j]);
							}
						}
					}
				}
				if(c == 'M' || c == 'L' || c == 'O'|| c == 'E'
				   || c == 'W' || c == 'H'){
				   Enemy *e = nullptr;
				   if(c == 'M')e = new Merchant;
				   if(c == 'L')e = new Halfling;
				   if(c == 'O')e = new Orc;
				   if(c == 'E')e = new Elf;
				   if(c == 'W')e = new Dwarf;
				   if(c == 'H')e = new Human;
				   floorInfo[i][j]->setEnemy(e);
				   enemyInfo.emplace_back(floorInfo[i][j]);
				}
			}
		}
	}		
		
		
	void Floor::generateAll(){
	// Call specific private method to random generate things
		generateHero();
		generateStair();
		for(int i=0;i<10;i++){
			generatePotion();
			generateGold();
		}
		for(int i=0;i<20;i++){
			generateEnemy();
		}
	}


	void Floor::generateHero(){
	// Randomly place the hero, track its location
		srand(time(NULL));
		while(true){
			int chamNum = rand()%5+1;
			int randIndex = rand()%(chamber[chamNum-1].size()-1);
			if (chamber[chamNum-1][randIndex]->isMoveable()) {
				this->heroCell = chamber[chamNum-1][randIndex];
				heroRow = heroCell->getRow();
				heroCol = heroCell->getCol();
				heroChamber = chamNum;
				if (levelNum == 1){action = "Player Character Has Spawned.";}
				else {action = "PC Enters Next Floor";}
				break;
			} 
		}
	}
		
		
	void Floor::generateStair(){
	// Generate a stair
		srand(time(NULL));
		while(true){
			int chamNum = rand()%5+1;
			int randIndex = rand()%(chamber[chamNum-1].size()-1);
			if(chamNum == heroChamber){
				continue; // Make sure stair and hero not in same chamber
			}
			if(chamber[chamNum-1][randIndex]->isMoveable()) {
				chamber[chamNum-1][randIndex]->setStair();
				break;
			} 
		}
	}
	
	
	void Floor::generatePotion(){
	// Randomly generate potions
		srand(time(NULL));
		while(true){
			int pType = rand()%6+1;
			int chamNum = rand()%5+1;
			int randIndex = rand()%(chamber[chamNum-1].size()-1);
			Cell *c = chamber[chamNum-1][randIndex];
			if (c->isOtherMoveable() && c != heroCell) {
				Potion *p = new Potion{pType};
				chamber[chamNum-1][randIndex]->setItem(p);
				break;
			} 
		}
	}		
	
	
	void Floor::generateGold(){
	// Randomly generate gold
		srand(time(NULL));
		while(true){
			int gType = rand()%8+1;
			int chamNum = rand()%5+1;
			int randIndex = rand()%(chamber[chamNum-1].size()-1);
			Cell *c = chamber[chamNum-1][randIndex];
			if (c->isOtherMoveable() && c != heroCell) {
				Gold *g = new Gold{gType};
				c->setItem(g);
				// A dragon generator is called when a dragon hoard is created
				if(c->getItemType() == "Dragon"){
					while(true){
						int dir = rand()%8+1;
					    if(generateDragon(g,c,dir)){
							break;
						}
					}
				}
				break;
			} 
		}
	}		
	
	
	bool Floor::generateDragon(Gold *hoard, Cell *cell, int dir){
	// Randomly generate a dragon in the random available position
	//  near the dragon hoard, return true if successfully generated.
		int r;
		int c;
		int row = cell->getRow();
		int col = cell->getCol();
		if(dir == 1){r = -1;c = 0;}
		if(dir == 2){r = 1;c = 0;}
		if(dir == 3){r = 0;c = -1;}
		if(dir == 4){r = 0;c = 1;}
		if(dir == 5){r = -1;c = -1;}
		if(dir == 6){r = -1;c = 1;}
		if(dir == 7){r = 1;c = -1;}
		if(dir == 8){r = 1;c = 1;}
		if(floorInfo[row+r][col+c]->getCellChar() == '.'){
			Enemy *e = new Dragon(hoard);
			floorInfo[row+r][col+c]->setEnemy(e);
			enemyInfo.emplace_back(floorInfo[row+r][col+c]);
			return true;
		}
		return false;
	}

	
	void Floor::generateEnemy(){
	// Randomly generate enemies on random cells, pass pointer to those cells
		srand(time(NULL));
		while(true){
			int chamNum = rand()%5+1;
			int randIndex = rand()%(chamber[chamNum-1].size()-1);
			int eType = rand()%18+1;
			if (chamber[chamNum-1][randIndex]->isOtherMoveable() &&
				chamber[chamNum-1][randIndex] != heroCell) {
				Enemy *e;
				if(eType>=1 && eType<=4){e = new Human;}
				if(eType>=5 && eType<=7){e = new Dwarf;}
				if(eType>=8 && eType<=12){e = new Halfling;}
				if(eType>=13 && eType<=14){e = new Elf;}
				if(eType>=15 && eType<=16){e = new Orc;}
				if(eType>=17 && eType<=18){e = new Merchant;}
				chamber[chamNum-1][randIndex]->setEnemy(e);
				enemyInfo.emplace_back(chamber[chamNum-1][randIndex]);
				break;
			} 
		}
	}
		

	void Floor::heroTakePotion(string dir){
	// Hero's take potion behavior
		int row;
		int col;
		if(dir == "no"){row = -1;col = 0;}
		else if(dir == "so"){row = 1;col = 0;}
		else if(dir == "we"){row = 0;col = -1;}
		else if(dir == "ea"){row = 0;col = 1;}
		else if(dir == "nw"){row = -1;col = -1;}
		else if(dir == "ne"){row = -1;col = 1;}
		else if(dir == "sw"){row = 1;col = -1;}
		else if(dir == "se"){row = 1;col = 1;}
		else {action = "Invalid direction."; return;}
		// Check if there is a potion
		if(floorInfo[heroRow+row][heroCol+col]->getCellChar() == 'P'){
			floorInfo[heroRow+row][heroCol+col]->getItem()->effectHero(h);
			string pType = floorInfo[heroRow+row][heroCol+col]->getItemType();
			h->learnPotion(pType);
			floorInfo[heroRow+row][heroCol+col]->resetItem();
			heroMove(dir,true);
			action = "PC uses " + pType;
		}
		// Give message if no potion in the given direction
		else action = "No potion in the given direction.";
	}


	void Floor::heroPickGold(Cell *gold){
	// If the gold is available, it adds to the hero's gold value
		if(gold->getItem()->effectHero(h)){
			gold->resetItem();
			action = "PC Picks Up Gold";
			pickGold = true;
		} else {
			pickGold = true;
			return;
		}
	}

	
	void Floor::heroAttack(string dir){
	// Hero attack behavior
		int row;
		int col;
		if(dir == "no"){row = -1;col = 0;}
		else if(dir == "so"){row = 1;col = 0;}
		else if(dir == "we"){row = 0;col = -1;}
		else if(dir == "ea"){row = 0;col = 1;}
		else if(dir == "nw"){row = -1;col = -1;}
		else if(dir == "ne"){row = -1;col = 1;}
		else if(dir == "sw"){row = 1;col = -1;}
		else if(dir == "se"){row = 1;col = 1;}
		else {action = "Invalid direction."; return;}
		Cell *c = floorInfo[heroRow+row][heroCol+col];
		if(c->getEnemy()){
			floorInfo[heroRow][heroCol]->setHeroCell();
			// If attacks a merchant, set its mode to hostile
			if(c->getCellChar() == 'M'){isMerchantBad = true;}
			action = c->getEnemy()->combat(h);
			// Check if hero is dead after the combar
			if(h->isDead()){return;}
			// Set the enemy being attacked to combat mode 
			combatAction = true;
			c->setAttacted();
			// Check if enemy is dead
			if(c->getEnemy()->isDead()){
				c->resetAll();
			}
			attackMode = true;
		}
		// If no enemy in the given direction, not moving
		floorInfo[heroRow][heroCol]->setHeroCell();
		action = "No enemy in the given direction. ";
	}
	

	void Floor::heroMove(string dir, bool usePotion){
	// Hero normal move behavior
		int row;
		int col;
		if(dir == "no"){row = -1;col = 0;dir = "North";}
		else if(dir == "so"){row = 1;col = 0;dir = "South";}
		else if(dir == "we"){row = 0;col = -1;dir = "West";}
		else if(dir == "ea"){row = 0;col = 1;dir = "East";}
		else if(dir == "nw"){row = -1;col = -1;dir = "North West";}
		else if(dir == "ne"){row = -1;col = 1;dir = "North East";}
		else if(dir == "sw"){row = 1;col = -1;dir = "South West";}
		else if(dir == "se"){row = 1;col = 1;dir = "South East";}
		else {action = "Invalid direction";return;}
		// If hero walks on gold, pick it up if available
		if(floorInfo[heroRow+row][heroCol+col]->getCellChar() == 'G'){
			heroPickGold(floorInfo[heroRow+row][heroCol+col]);
		}
		// Check if the give direction is standable
		if(floorInfo[heroRow+row][heroCol+col]->isMoveable()){
			heroRow += row;
			heroCol += col;
			heroCell = floorInfo[heroRow][heroCol];
			floorInfo[heroRow][heroCol]->setHeroCell();
			if(!usePotion && !pickGold){action = "PC Moves " + dir;}
			pickGold = false;
		} else{
			floorInfo[heroRow][heroCol]->setHeroCell();
			action = "You shall not pass!!";
		}
	}


	void Floor::enemyMove(){
	// Enemy's auto attack behavior
		srand(time(NULL));
		// Loop through enemy cell vector
		for(unsigned int i=0;i<enemyInfo.size();i++){
			Cell *cp = enemyInfo[i];
			if(!cp->getEnemy())continue;  // Check if the enemy is dead 
			if(cp->isAttacked())continue; // Check the enemy is being attacked
			// Check if the enemy finds hero is nearby,
			// If is merchant and merchant is bad, attack
			if((cp->isFighting() && cp->getCellChar() != 'M') ||
			   (cp->getCellChar() == 'M' && isMerchantBad)) {     
				if(!combatAction)action = "";
				combatAction = true;
                // Conduct combat				
				action += cp->getEnemy()->combat(h);
				// Check if hero or enemy is dead
				if(h->isDead()){return;}
				if(cp->getEnemy()->isDead()){
					cp->resetAll();
				}
				continue;
			}
			// If a enemy is not in combat state, resume its random movement
			while(true){
				if(enemyFroze){break;}
				if(cp->getCellChar() == 'D'){break;}
				int r;
				int c;
				int dir = rand()%8+1;
				int row = cp->getRow();
				int col = cp->getCol();
				// Randomly choose a valid direction
				if(dir == 1){r = -1;c = 0;}
				if(dir == 2){r = 1;c = 0;}
				if(dir == 3){r = 0;c = -1;}
				if(dir == 4){r = 0;c = 1;}
				if(dir == 5){r = -1;c = -1;}
				if(dir == 6){r = -1;c = 1;}
				if(dir == 7){r = 1;c = -1;}
				if(dir == 8){r = 1;c = 1;}
				if(floorInfo[row+r][col+c]->isOtherMoveable() &&
				   floorInfo[row+r][col+c] != heroCell){
					floorInfo[row+r][col+c]->setEnemy(cp->getEnemy());
					enemyInfo[i]->resetEnemy();
					enemyInfo[i] = floorInfo[row+r][col+c];
					break;
				}
			}
		}
	}

	
	void Floor::frozeEnemy(){
		// Check if enemy is frozen
		enemyFroze = !enemyFroze;
		if(enemyFroze){action = "Enemy Frozen.";}
		else{action = "Enemy Defrozen.";}
	}
	
	
	void Floor::checkAround(){
	// Hero checks around, send message if sees any potion or gold
		if(attackMode){
			enemyMove();
			attackMode = false;
			return;
		}
		for(int i=heroRow-1; i<=heroRow+1; i++){
			for(int j=heroCol-1; j<=heroCol+1; j++){
				if(floorInfo[i][j]->getCellChar() == 'P'){
					string pType = floorInfo[i][j]->getItemType();
					if (h->checkIfKnown(pType)){action += " and Sees a " + pType;}
					else{action += " and Sees an unknown Potion";}
				}
				if(floorInfo[i][j]->getCellChar() == 'G'){
					string pType = floorInfo[i][j]->getItemType();
					action += " and Sees Gold";
				}
			}
		}
		// Enemy moves after hero checks around
		enemyMove();
	}
			
			
	bool Floor::reachStair(){
	// Check if hero reaches the stair
		if(heroCell->getCellChar() == '\\'){
			levelNum++;
			return true;
		}
		return false;
	}
	

	void Floor::displayScore() const{
	// Display score
		int score = h->getGold();
		if (h->getRace() == "Shade"){
			score *= 1.5;  // Bonus for shade
		}
		cout << "Score: " << score << endl;
	}
	
	
	void Floor::printHeroInfo(){
	// Print action informaton
		cout << "Race: " << h->getRace() << "  " << "Gold: " << h->getGold();
		cout << setw(55) << setiosflags(ios::right) << "Floor " << levelNum << endl;
		cout << "HP: " << h->getHp() << endl;
		cout << "Atk: " << h->getAtk() << endl;
		cout << "Def: " << h->getDef() << endl;
		cout << "Action: " << action << endl;
		action = "";
		combatAction = false;
		attackMode = false;
	}


	void Floor::printFloor(){
	// Print the game board and informarion
		if(h->getRace() == "Troll"){h->modifyHp(5);}
		for(int i = 0; i < 25; i++) {
			for(int j = 0; j < 79; j++) {
				if(i == heroRow && j == heroCol){
					cout << '@';
				} else if(floorInfo[i][j]->getCellChar() == '@'){
					cout << '.';
				} else floorInfo[i][j]->printCell();
			}
			cout << endl;
		}
		printHeroInfo();
	}


	void Floor::clearBoard(){
	// Clear the game board
		for(int i=0; i<25; i++){
			for(int j=0; j<79; j++){
				delete floorInfo[i][j];
			}
		}
	}


