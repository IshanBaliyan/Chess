#include "human.h"

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

Human::Human(string name, string type, Piece* board) : name{name}, type{type}, board{board} {}

// Get human's next move from cin as input
string Human::getMove() const {
    string currIn;
    getline(cin, currIn);

    return currIn;
}

string Human::getName() const {
    return name;
}

string Human::getType() const {
    return type;
}
