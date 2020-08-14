#ifndef HERO_H
#define HERO_H
#include <string>
#include <vector>
class Hero {
	int hp;
	int atk;
	int def;
	std::string race = "Shade";
	const int defaultHp;
	const int defaultAtk;
	const int defaultDef;
	std::vector<std::string> knownPotion;
	int gold = 0;
	public:
		Hero(int hp, int atk, int def, std::string race);
		~Hero();
		std::string getRace();
		int getGold();
		int getHp();
		int getAtk();
		int getDef();
		void modifyHp(int value);
		void modifyAtk(int value);
		void modifyDef(int value);
		void modifyGold(int value);
		bool isDead() const;
		void resetState();
		void learnPotion(std::string);
		bool checkIfKnown(std::string);
		
};
#endif
