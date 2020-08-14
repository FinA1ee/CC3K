#ifndef DWARF_H
#define DWARF_H
#include "enemy.h"
#include <string>
class Dwarf: public Enemy{
	int hp = 100;
	double atk = 20;
	double def = 30;
	bool hostileState = true;
	public:
		char getChar() const override;
		void printEnemy() const override; 
		int getHp() const override;
		int getAtk() const override;
		int getDef() const override;
		bool isDead() const override;
		bool isHostile() const override;
		std::string combat(Hero *h) override;
};

#endif


