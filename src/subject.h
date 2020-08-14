#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "subscriptiontype.h"
class Observer;

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach(Observer *o);  
  void notifyObservers(SubscriptionType st);
  virtual ~Subject() = 0;
};

#endif


