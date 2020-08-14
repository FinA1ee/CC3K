#include "hero.h"
#include <vector>
using namespace std;

Hero::Hero(int hp, int atk, int def, std::string race):
		hp{hp}, atk{atk}, def{def}, race{race}, defaultHp{hp}, defaultAtk{atk}, defaultDef{def}{}

		
		
Hero::~Hero(){}

string Hero::getRace(){return race;}

int Hero::getHp(){
	if(race != "Vampire" && hp > defaultHp){
		hp = defaultHp;
	}
	if (hp <= 0){return 0;}
	return hp;
}


int Hero::getAtk(){
	if(atk < 0){return 0;}
	return atk;
}
int Hero::getDef(){
	if(def < 0){return 0;}
	return def;
}
int Hero::getGold(){return gold;}


void Hero::modifyHp(int value){hp+=value;}
void Hero::modifyAtk(int value){atk+=value;}
void Hero::modifyDef(int value){def+=value;}
void Hero::modifyGold(int value){gold+=value;}

void Hero::resetState(){
	atk = defaultAtk;
	def = defaultDef;
	knownPotion.clear();
}

bool Hero::isDead() const{
	if(hp <= 0){return true;}
	else {return false;}
}	
	

void Hero::learnPotion(string pType){
	knownPotion.emplace_back(pType);
}

bool Hero::checkIfKnown(string pType){
	for(unsigned int i=0; i<knownPotion.size();i++){
		if(knownPotion[i] == pType){
			return true;
		}
	}
	return false;
}










