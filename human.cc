#include "human.h"

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

Human::Human(string type, string colour, Piece* board) :type{type}, colour{colour}, board{board} {}

// Get human's next move from cin as input
string Human::getMove() {
    string currIn;
    getline(cin, currIn);

    return currIn;
}

string Human::getType() const {
    return type;
}

string Human::getColour() const {
    return colour;
}
