// invalidmoveexception.cc
#include "invalidmoveexception.h"
#include <string>
using namespace std;

InvalidMoveException::InvalidMoveException(string varExcept) : varExcept{varExcept} {}

InvalidMoveException::InvalidMoveException() : varExcept{""} {}

string InvalidMoveException::getVarExcept() const {
    return varExcept;
}

InvalidMoveException::~InvalidMoveException(){}


