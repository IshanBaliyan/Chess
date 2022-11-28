// decorator.cc
#include "piece.h"
#include "decorator.h"

Decorator::Decorator(Piece *comp) : comp{comp} {}

Decorator::~Decorator() { delete comp; }


