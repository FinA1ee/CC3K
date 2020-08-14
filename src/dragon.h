#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"
#include "gold.h"
#include <string>
class Hero;
class Dragon: public Enemy{
	int hp = 150;
	double atk = 20;
	double def = 20;
	Gold *dragonHoard;
	bool hostileState = true;
	public:
		Dragon(Gold *dragonHoard);
		char getChar() const override;
		int getHp() const override;
		int getAtk() const override;
		int getDef() const override;
		bool isDead() const override;
		void printEnemy() const override;
		bool isHostile() const override;
		std::string combat(Hero *h) override;
};
#endif


