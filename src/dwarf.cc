#include <iostream>
#include <string>
#include "enemy.h"
#include "dwarf.h"
#include "hero.h"
#include <cstdlib>
#include <ctime>
using namespace std;


void Dwarf::printEnemy() const{cout << "W";}

char Dwarf::getChar() const{return 'W';} 

int Dwarf::getHp() const{return hp;}

int Dwarf::getAtk() const{return atk;}

int Dwarf::getDef() const{return def;}

bool Dwarf::isDead() const{
	if(hp <= 0){
		return true;
	}
	return false;
}


string Dwarf::combat(Hero *h){
	srand(time(NULL));
	int miss = rand()%2+1;
	string result;
	double heroAtk = h->getAtk();
	double heroDef = h->getDef();
	int hpLose = (100/(100+def)) * heroAtk;
	int hpLoseH = (100/(100+heroDef)) * atk;
	hp -= hpLose;
	result = "PC Deals " + to_string(hpLose) + " Damage to W(" + to_string(hp) + "). ";
	if(h->getRace() == "Vampire"){h->modifyHp(-5);}
	if(hp <= 0){
		int gold = rand()%2+1;
		h->modifyGold(gold);
		if(h->getRace() == "Goblin"){h->modifyGold(5);}
		return "PC Slains W. ";
	}
	
	if(miss == 1){result += "W Misses. ";}
	else{
		result += "W Deals " + to_string(hpLoseH) + " Damage to PC. ";
		h->modifyHp(-hpLoseH);
	}
	if(h->isDead())result+= "PC is slained by W. ";
	return result;
}

bool Dwarf::isHostile() const{
	return hostileState;
}





