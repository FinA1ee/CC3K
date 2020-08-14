#include "enemy.h"
#include "dragon.h"
#include <iostream>
#include <string>
using namespace std;

Dragon::Dragon(Gold *dragonHoard):dragonHoard{dragonHoard}{}

char Dragon::getChar() const{return 'D';}

void Dragon::printEnemy() const {cout << "D";}

int Dragon::getHp() const{return hp;}

int Dragon::getAtk() const{return atk;}

int Dragon::getDef() const{return def;}

bool Dragon::isDead() const{
	if(hp <= 0){
		dragonHoard->setAvail();
		return true;
	}
	return false;
}


string Dragon::combat(Hero *h){
	srand(time(NULL));
	int miss = rand()%2+1;
	string result;
	double heroAtk = h->getAtk();
	double heroDef = h->getDef();
	int hpLose = (100/(100+def)) * heroAtk;
	int hpLoseH = 0;
	hp -= hpLose;
	result = "PC Deals " + to_string(hpLose) + " Damage to D(" + to_string(hp) + "). ";
	if(h->getRace() == "Vampire"){h->modifyHp(5);}
	if(hp <= 0){
		if(h->getRace() == "Goblin"){h->modifyGold(5);}
		return "PC Slains Dragon. ";
	}
	if(miss == 1){
		result += "D Misses. ";
	}else{
		hpLoseH = (100/(100+heroDef)) * atk;
		result += "D Deals " + to_string(hpLoseH) + " Damage to PC. ";
	}
	h->modifyHp(-hpLoseH);
	if(h->isDead())result+= "PC is slained by Dragon. ";
	return result;
}


bool Dragon::isHostile() const{
	return hostileState;
}

