#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include <vector>
class Hero;
class Enemy {
	public:
		virtual char getChar() const = 0;
		virtual	void printEnemy() const = 0;
		virtual int getHp() const = 0;
		virtual int getAtk() const = 0;
		virtual int getDef() const = 0;
		virtual bool isDead() const = 0;
		virtual bool isHostile() const = 0;
		virtual std::string combat(Hero *h) = 0;
		virtual ~Enemy() = default;
};
#endif


