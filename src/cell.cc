#include "cell.h"
#include "observer.h"
#include "subject.h"
#include "subscriptiontype.h"
#include "enemy.h"
#include "item.h"
#include <iostream>
#include <utility>
using namespace std;

	Cell::Cell(int row, int col, char cellChar): 
		  row{row}, col{col}, cellChar{cellChar}{}
	
	Cell::~Cell(){
		if(e)delete e;
		if(it)delete it;
	}
	
	void Cell::setStair(){
	// Set stair cell
		this->stair = true;
		cellChar = '\\';
	}
		
	void Cell::setEnemy(Enemy* e){
	// Set enemy cell
		this->e = e;
		this->isTaken = true;
		cellChar = e->getChar();
	}
	
	void Cell::resetEnemy(){
	// Reset enemy cell
		this->e = nullptr;
		this->isTaken = false;
		cellChar = '.';
	}
	
	void Cell::setItem(Item* it){
	// Set item cell
		this->it = it;
		this->isTaken = true;
		cellChar = it->getChar();
	}
	
	void Cell::resetItem(){
	// Reset item cell
		delete it;
		this->it = nullptr;
		this->isTaken = false;
		cellChar = '.';
	}
	
	const char Cell::getCellChar() const{return cellChar;}
	
	string Cell::getItemType() const{
		return it->getType();
	}
		
	Enemy* Cell::getEnemy() {return e;} 
		
	Item* Cell::getItem() {return it;}
    
	// Return cell information
	const int Cell::getRow() const {return row;}
	
	const int Cell::getCol() const {return col;}
	
	bool Cell::isMoveable(){
	// Check if a cell is standable for hero
		if(cellChar == 'G'){return true;}
		if(isTaken) return false;
		else if(cellChar == '.' || cellChar == '+' || cellChar == '#' || cellChar == '\\') {
			return true;
		} else {
			return false;
		}
	}
	
	
	bool Cell::isOtherMoveable(){
	// Check if a cell is standable for enemy
		if(isTaken) return false;
		else if (cellChar == '.'){return true;}
		else return false;
	}
			
			
	void Cell::printCell(){
		if(it) it->printItem();
		else if(e) e->printEnemy();
		else cout << cellChar;
		isEnemyCombat = false;
		isEnemyAttacked = false;
	}
	
	void Cell::setHeroCell(){
	// Notify observers with specific subscription type
		notifyObservers(SubscriptionType::Enemy);
		notifyObservers(SubscriptionType::DragonHoard);
	}
	
	SubscriptionType Cell::subType() const{
	// Return a cell's subscription type
		if(e && e->getChar() == 'D'){return SubscriptionType::DragonHoard;}
		if(it && it->getType() == "Dragon"){return SubscriptionType::DragonHoard;}
		else if(e){return SubscriptionType::Enemy;}
		else{return SubscriptionType::Nothing;}
	}
	
	// Return and modify states of enemy cells
	bool Cell::isFighting() const{return isEnemyCombat;}
	
	void Cell::setAttacted(){isEnemyAttacked = true;}
	
	bool Cell::isAttacked() const{return isEnemyAttacked;}
	
	// When a cell is notified, set states
	void Cell::notify(Subject &whoNotified){
		if(it && it->getType() == "Dragon"){
			notifyObservers(SubscriptionType::DragonHoard);
		}
		isEnemyCombat = true;
	}
		
		
	void Cell::resetAll(){
		if(e) {
			cellChar = '.';
			delete e;
			e = nullptr;
		}
		if(it) {
			cellChar = '.';
			delete it;
			it = nullptr;
		}
		if(stair){
			cellChar = '.';
			stair = false;
		}
		isTaken = false;
	
	}
	
	
	void Cell::resetHero(){
		if(cellChar == '@'){
			cellChar = '.';
		}
		return;
	}
	
	
	
	
	