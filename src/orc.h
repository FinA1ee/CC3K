#ifndef ORC_H
#define ORC_H
#include "enemy.h"
#include <string>
class Orc: public Enemy{
	int hp = 180;
	double atk = 30;
	double def = 25;
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
