#include <iostream>
#include <string>
#include "enemy.h"
#include "elf.h"
#include "hero.h"
#include <cstdlib>
#include <ctime>
using namespace std;


void Elf::printEnemy() const{cout << "E";}

char Elf::getChar() const{return 'E';} 

int Elf::getHp() const{return hp;}

int Elf::getAtk() const{return atk;}

int Elf::getDef() const{return def;}

bool Elf::isDead() const{
	if(hp <= 0){
		return true;
	}
	return false;
}


string Elf::combat(Hero *h){
	srand(time(NULL));
	int miss = rand()%2+1;
	string result;
	double heroAtk = h->getAtk();
	double heroDef = h->getDef();
	int hpLose = (100/(100+def)) * heroAtk;
	int hpLoseH = (100/(100+heroDef)) * atk;
	hp -= hpLose;
	result = "PC Deals " + to_string(hpLose) + " Damage to E(" + to_string(hp) + "). ";
	if(h->getRace() == "Vampire"){h->modifyHp(5);}
	if(hp <= 0){
		int gold = rand()%2+1;
		h->modifyGold(gold);
		if(h->getRace() == "Goblin"){h->modifyGold(5);}
		return "PC Slains E. ";
	}
	if(miss == 1){result += "E Misses. ";} 
	else{
		result += "E Deals " + to_string(hpLoseH) + " Damage to PC. ";
		h->modifyHp(-hpLoseH);
	}
	if(h->isDead()){result+= "PC is slained by E. "; return result;}
	if(h->getRace() != "Drow"){
		miss = rand()%2+1;
		if(miss == 1){result += "E Misses. ";}
		else{
			result += "E Deals " + to_string(hpLoseH) + " Damage to PC. ";
			h->modifyHp(-hpLoseH);
		}
	}
	if(h->isDead()){result+= "PC is slained by E. "; return result;}
	return result;
}

bool Elf::isHostile() const{
	return hostileState;
}





