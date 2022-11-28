#include "queen.h"
#include "piece.h"
#include <string>

Queen::Queen(Board* board, string name, string colour, int x, int y, Piece *comp) : Decorator{comp}, board{board}, name{name}, colour{colour}, x{x}, y{y} {}

void Queen::makeMove(Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){
    //TODO: [ADD CODE HERE]
}

// Only implement the following method for the PAWN (skip for other pieces)
// Method for pawn (only implement for pawn), where pawn reaches end of
// board and must be changed to one of Queen, Rook, Bishop, Knight
void Queen::makeMove(string replacePiece, Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){}


bool Queen::willNextMoveCauseCheck(int newX, int newY){
    //TODO: [ADD CODE HERE]
}

bool Queen::willNextMoveStopCurrentCheck(int newX, int newY){
    //TODO: [ADD CODE HERE]
}

string Queen::getColour() const {
    return colour;
}

int Queen::getX() const {
    return x;
}

int Queen::getY() const {
    return y;
}

Board* Queen::getBoard() const {
    return board;
}

string Queen::getName() const {
    return name;
}

