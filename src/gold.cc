#include "item.h"
#include "gold.h"
#include "hero.h"
#include <iostream>
#include <string>
using namespace std;

Gold::Gold(int gInt) {
	if (gInt == 1 || gInt == 2){
		gT = "Small";
		isAvailable = true;
	} else if (gInt == 3) {
		gT = "Dragon";
		isAvailable = false;
	} else if (gInt == 10) {
		gT = "Merchant";
		isAvailable = true;
	} else {
		gT = "Normal";
		isAvailable = true;
	}
}
	
void Gold::printItem() const {cout << "G";}
	
char Gold::getChar() const {return 'G';}

string Gold::getType() const {return gT;}

void Gold::setAvail() {isAvailable = !isAvailable;}


bool Gold::effectHero(Hero *h) {
	if(isAvailable){
		if (gT == "Small") h->modifyGold(1);
		else if (gT == "Normal") h->modifyGold(2);
		else if (gT == "Dragon") h->modifyGold(6);
		else if (gT == "Merchant") h->modifyGold(4);
		return true;
	} else {
		return false;
	}
}



