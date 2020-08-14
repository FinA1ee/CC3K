#include <iostream>
#include <string>
#include "enemy.h"
#include "merchant.h"
#include "hero.h"
#include <cstdlib>
#include <ctime>
using namespace std;


void Merchant::printEnemy() const{cout << "M";}

char Merchant::getChar() const{return 'M';} 

int Merchant::getHp() const{return hp;}

int Merchant::getAtk() const{return atk;}

int Merchant::getDef() const{return def;}

bool Merchant::isDead() const{
	if(hp <= 0){
		return true;
	}
	return false;
}


string Merchant::combat(Hero *h){
	srand(time(NULL));
	int miss = rand()%2+1;
	string result;
	double heroAtk = h->getAtk();
	double heroDef = h->getDef();
	int hpLose = (100/(100+def)) * heroAtk;
	int hpLoseH = (100/(100+heroDef)) * atk;;
	hp -= hpLose;
	result = "PC Deals " + to_string(hpLose) + " Damage to M(" + to_string(hp) + "). ";	
	if(h->getRace() == "Vampire"){h->modifyHp(5);}
	if(hp <= 0){
		h->modifyGold(4);
		if(h->getRace() == "Goblin"){h->modifyGold(5);}
		result = "PC Slains M. Picks up Merchant Hoard. ";
		return result;
	}
	
	if(miss == 1){result += "M Misses. ";}
	else{		
		result += "M Deals " + to_string(hpLoseH) + " Damage to PC. ";
		h->modifyHp(-hpLoseH);
	}
	if(h->isDead())result+= "PC is slained by M. ";
	return result;
}

bool Merchant::isHostile() const{
	return hostileState;
}





