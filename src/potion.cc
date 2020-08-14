#include "potion.h"
#include "item.h"
#include <iostream>
#include <string>
using namespace std;

Potion::Potion(int pInt) {
	if (pInt == 1){
		pType = "RH";
	} else if (pInt == 2) {
		pType = "BA";
	} else if (pInt == 3) {
		pType = "BD";
	} else if (pInt == 4) {
		pType = "PH";
	} else if (pInt == 5) {
		pType = "WA";
	} else if (pInt == 6) {
		pType = "WD";
	}
}
	
void Potion::printItem() const {cout << "P";}

char Potion::getChar() const {return 'P';}

string Potion::getType() const {return pType;}



bool Potion::effectHero(Hero *h) {
	double effect = 1;
	if (h->getRace() == "Drow") {effect = 1.5;}
	if (pType == "RH") h->modifyHp(10 * effect);
	else if (pType == "BA") h->modifyAtk(5 * effect);
	else if (pType == "BD") h->modifyDef(5 * effect);
	else if (pType == "PH") h->modifyHp(-10 * effect);
	else if (pType == "WA") h->modifyAtk(-5 * effect);
	else if (pType == "WD") h->modifyAtk(-5 * effect);
	return true;
}
	
	