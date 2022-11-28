// blank.cc

#include "blank.h"
#include <string>
using namespace std;

void Blank::makeMove(Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){
    return false; // impossible for blank space to make a move, so returning false
}

// Only implement the following method for the PAWN (skip for other pieces)
// Method for pawn (only implement for pawn), where pawn reaches end of
// board and must be changed to one of Queen, Rook, Bishop, Knight
void Blank::makeMove(string replacePiece, Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){}


bool Blank::willNextMoveCauseCheck(int newX, int newY){
    return false; // impossible for blank space to make a move, so returning false
}

bool Blank::willNextMoveStopCurrentCheck(int newX, int newY){
    return false; // impossible for blank space to make a move, so returning false
}

string Blank::getColour() const {
    return colour;
}

int Blank::getX() const {
    return x;
}

int Blank::getY() const {
    return y;
}

Board* Blank::getBoard() const {
    return board;
}

string Blank::getName() const {
    return name;
}

