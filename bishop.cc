#include "bishop.h"
#include "piece.h"
#include <string>

Bishop::Bishop(Board* board, string name, string colour, int x, int y, Piece *comp) : Decorator{comp}, board{board}, name{name}, colour{colour}, x{x}, y{y} {}

void Bishop::makeMove(Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){
    //TODO: [ADD CODE HERE]
}

// Only implement the following method for the PAWN (skip for other pieces)
// Method for pawn (only implement for pawn), where pawn reaches end of
// board and must be changed to one of Queen, Rook, Bishop, Knight
void Bishop::makeMove(string replacePiece, Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){}


bool Bishop::willNextMoveCauseCheck(int newX, int newY){
    //TODO: [ADD CODE HERE]
}

bool Bishop::willNextMoveStopCurrentCheck(int newX, int newY){
    //TODO: [ADD CODE HERE]
}

string Bishop::getColour() const {
    return colour;
}

int Bishop::getX() const {
    return x;
}

int Bishop::getY() const {
    return y;
}

Board* Bishop::getBoard() const {
    return board;
}

string Bishop::getName() const {
    return name;
}

