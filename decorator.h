// decorator.h
#ifndef _DECORATOR_H_
#define _DECORATOR_H_
#include "piece.h"

class Decorator : public Piece {
  protected:
    Piece *comp;
  public:
    Decorator(Piece *comp);
    virtual ~Decorator();
};

#endif

