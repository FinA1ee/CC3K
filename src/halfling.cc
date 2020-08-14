#include <iostream>
#include <string>
#include "enemy.h"
#include "halfling.h"
#include "hero.h"
#include <cstdlib>
#include <ctime>
using namespace std;


void Halfling::printEnemy() const{cout << "L";}

char Halfling::getChar() const{return 'L';} 

int Halfling::getHp() const{return hp;}

int Halfling::getAtk() const{return atk;}

int Halfling::getDef() const{return def;}

bool Halfling::isDead() const{
	if(hp <= 0){
		return true;
	}
	return false;
}


string Halfling::combat(Hero *h){
	srand(time(NULL));
	int miss = rand()%2+1;
	string result;
	double heroAtk = h->getAtk();
	double heroDef = h->getDef();
	int hpLose = (100/(100+def)) * heroAtk;
	int hpLoseH = (100/(100+heroDef)) * atk;;
	int hMiss = rand()%2+1;
	if(hMiss == 1){
		hp -= hpLose;
		result = "PC Deals " + to_string(hpLose) + " Damage to L(" + to_string(hp) + "). ";
		if(h->getRace() == "Vampire"){h->modifyHp(5);}
	} else {result = "PC Misses. ";}
	
	if(hp <= 0){
		int gold = rand()%2+1;
		h->modifyGold(gold);
		if(h->getRace() == "Goblin"){h->modifyGold(5);}
		return "PC Slains L. ";
	}
	
	if(miss == 1){result += "L Misses. ";} 
	else{
		result += "L Deals " + to_string(hpLoseH) + " Damage to PC. ";
		h->modifyHp(-hpLoseH);
	}
	if(h->isDead())result+= "PC is slained by L. ";
	return result;
}

bool Halfling::isHostile() const{
	return hostileState;
}





