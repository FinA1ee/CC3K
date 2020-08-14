#include "subject.h"
#include "observer.h"
#include "subscriptiontype.h"
using namespace std;

// Push new Observer ptr.
void Subject::attach(Observer *o) {
	observers.emplace_back(o);
}

// Go through vector of Observer and notify those with subscriptionType t.
void Subject::notifyObservers(SubscriptionType st) {
	int size = observers.size();
	for(int i = 0; i < size; i++) {
		if (st == observers[i]->subType()){
			observers[i]->notify(*this);
		}
	}
}

Subject::~Subject() {};

