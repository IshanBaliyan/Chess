#include "knight.h"
#include "piece.h"
#include <string>

Knight::Knight(Board* board, string name, string colour, int x, int y, Piece *comp) : Decorator{comp}, board{board}, name{name}, colour{colour}, x{x}, y{y} {}

void Knight::makeMove(Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){
    //TODO: [ADD CODE HERE]
}

// Only implement the following method for the PAWN (skip for other pieces)
// Method for pawn (only implement for pawn), where pawn reaches end of
// board and must be changed to one of Queen, Rook, Bishop, Knight
void Knight::makeMove(string replacePiece, Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){}


bool Knight::willNextMoveCauseCheck(int newX, int newY){
    //TODO: [ADD CODE HERE]
}

bool Knight::willNextMoveStopCurrentCheck(int newX, int newY){
    //TODO: [ADD CODE HERE]
}

string Knight::getColour() const {
    return colour;
}

int Knight::getX() const {
    return x;
}

int Knight::getY() const {
    return y;
}

Board* Knight::getBoard() const {
    return board;
}

string Knight::getName() const {
    return name;
}

