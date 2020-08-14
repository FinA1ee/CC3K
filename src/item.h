#ifndef ITEM_H
#define ITEM_H
#include <string>
class Hero;
class Item {
	public:
		virtual void printItem() const = 0;
		virtual char getChar() const = 0;
		virtual std::string getType() const = 0;
		virtual bool effectHero(Hero *h) = 0;
		virtual ~Item() = default;
};
#endif

