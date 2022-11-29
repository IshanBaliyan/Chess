#include "computer.h"

#include <string>
using namespace std;

Computer::Computer(string name, string type, Piece* board) : name{name}, type{type}, board{board} {}

// Computer returns strategic move
string Computer::getMove() const {
    // TODO: [Insert Code for finding strategic move]
    // 4 levels of computer
}

string Computer::getName() const {
    return name;
}

string Computer::getType() const {
    return type;
}
