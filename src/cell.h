#ifndef CELL_H
#define CELL_H
#include "item.h"
#include "observer.h"
#include "subject.h"
#include "subscriptiontype.h"
#include <iostream>
#include <string>
#include "hero.h"
#include "enemy.h"

class Cell :public Observer, public Subject{
		int row;
		int col;
		char cellChar;
		bool isTaken = false;
		bool stair = false;
		bool isEnemyCombat = false;
		bool isEnemyAttacked = false;
		Item *it = nullptr;
		Enemy *e = nullptr;

	public:
		Cell(int row, int col, char cellChar); // Ctor
		~Cell();                        // Dtor
		
		void setItem(Item* it);          // Set ptr by depending on type of cell
		void resetItem();
	
		void setEnemy(Enemy *e);
		void resetEnemy();
		
		void setStair();
			
		const char getCellChar() const;  // Return field info 	
		std::string getItemType() const;
		
		const int getRow() const;
		const int getCol() const;
		
		Enemy* getEnemy();
		Item* getItem();		
		 
		
		bool isMoveable();               // Check if moveable
		bool isOtherMoveable();
		void printCell(); 	  
		
		void setHeroCell();
		
		bool isFighting() const;
		
		void setAttacted();
		bool isAttacked() const;
		
		void resetAll();
		
		
		void resetHero();
		
		SubscriptionType subType() const override;
		void notify(Subject &whoNotified) override; 
};
	
#endif












