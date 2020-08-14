#ifndef HUMAN_H
#define HUMAN_H
#include "enemy.h"
#include <string>
class Human: public Enemy{
	int hp = 140;
	double atk = 20;
	double def = 20;
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
