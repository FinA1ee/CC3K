#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemy.h"
#include <string>
class Merchant: public Enemy{
	int hp = 30;
	double atk = 70;
	double def = 5;
	bool hostileState = false;
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
