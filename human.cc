#include "human.h"
#include <string>
#include <iostream>
using namespace std;

Human::Human(string name, string type, Piece*board) : name{name}, type{type}, board{board} {} 

// Get human's next move from cin as input
string Human::getMove() const{
    // TODO; [Insert code for CIN the human's next move]
}

string Human::getName() const{
    return name;
}

string Human::getType() const{
    return type;
}




