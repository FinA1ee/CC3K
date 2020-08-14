#include <iostream>
#include <string>
#include "enemy.h"
#include "human.h"
#include "hero.h"
#include <cstdlib>
#include <ctime>
using namespace std;


void Human::printEnemy() const{cout << "H";}

char Human::getChar() const{return 'H';} 

int Human::getHp() const{return hp;}

int Human::getAtk() const{return atk;}

int Human::getDef() const{return def;}

bool Human::isDead() const{
	if(hp <= 0){
		return true;
	}
	return false;
}


string Human::combat(Hero *h){
	srand(time(NULL));
	int miss = rand()%2+1;
	string result;
	double heroAtk = h->getAtk();
	double heroDef = h->getDef();
	int hpLose = (100/(100+def)) * heroAtk;
	int hpLoseH = 0;
	hp -= hpLose;
	result = "PC Deals " + to_string(hpLose) + " Damage to H(" + to_string(hp) + "). ";
	if(h->getRace() == "Vampire"){h->modifyHp(5);}
	if(hp <= 0){
		h->modifyGold(4);
		if(h->getRace() == "Goblin"){h->modifyGold(5);}
		return "PC Slains H. ";
	}
	if(miss == 1){
		result += "H Misses. ";
	}else{
		hpLoseH = (100/(100+heroDef)) * atk;
		result += "H Deals " + to_string(hpLoseH) + " Damage to PC. ";
	}
	h->modifyHp(-hpLoseH);
	if(h->isDead())result+= "PC is slained by H. ";
	return result;
}

bool Human::isHostile() const{
	return hostileState;
}





