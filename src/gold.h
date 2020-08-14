#ifndef GOLD_H
#define GOLD_H
#include "item.h"
#include "hero.h"
#include <string>
class Gold : public Item{
	std::string gT;
	Hero *h;
	bool isAvailable;
	public:
		Gold(int gInt);
		void printItem() const override;
		char getChar() const override;
		std::string getType() const override;
		bool effectHero(Hero *h) override;
		void setAvail();
};
#endif

