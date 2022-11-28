// subject.h

// From course notes:
#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "piece.h"

class Observer;

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers();
  virtual Piece* getState(int x, int y) const = 0;
  virtual ~Subject() = default;
};

#endif

