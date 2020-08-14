#include <iostream>
#include <string>
#include "enemy.h"
#include "orc.h"
#include "hero.h"
#include <cstdlib>
#include <ctime>
using namespace std;


void Orc::printEnemy() const{cout << "O";}

char Orc::getChar() const{return 'O';} 

int Orc::getHp() const{return hp;}

int Orc::getAtk() const{return atk;}

int Orc::getDef() const{return def;}

bool Orc::isDead() const{
	if(hp <= 0){
		return true;
	}
	return false;
}


string Orc::combat(Hero *h){
	srand(time(NULL));
	int miss = rand()%2+1;
	string result;
	double heroAtk = h->getAtk();
	double heroDef = h->getDef();
	int hpLose = (100/(100+def)) * heroAtk;
	int hpLoseH = (100/(100+heroDef)) * atk;
	if(h->getRace() == "Goblin"){hpLoseH *= 1.5;}
	hp -= hpLose;
	result = "PC Deals " + to_string(hpLose) + " Damage to O(" + to_string(hp) + "). ";
	if(h->getRace() == "Vampire"){h->modifyHp(5);}
	if(hp <= 0){
		int gold = rand()%2+1;
		h->modifyGold(gold);
		if(h->getRace() == "Goblin"){h->modifyGold(5);}
		return "PC Slains O. ";
	}
	if(miss == 1){result += "O Misses. ";}
	else{
		result += "O Deals " + to_string(hpLoseH) + " Damage to PC. ";
		h->modifyHp(-hpLoseH);
	}
	if(h->isDead()){result+= "PC is slained by O. ";}
	return result;
}

bool Orc::isHostile() const{
	return hostileState;
}





