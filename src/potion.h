#ifndef POTION_H
#define POTION_H
#include "item.h"
#include "hero.h"
#include <string>

class Potion : public Item{
	std::string pType;
	bool isReveal = false;
	public:
		Potion(int pInt);
		void printItem() const override;
		char getChar() const override;
		std::string getType() const override;
		bool effectHero(Hero *h) override;
};
#endif



