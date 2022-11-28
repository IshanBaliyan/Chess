#include "rook.h"
#include "piece.h"
#include <string>

Rook::Rook(Board* board, string name, string colour, int x, int y, Piece *comp) : Decorator{comp}, board{board}, name{name}, colour{colour}, x{x}, y{y} {}

void Rook::makeMove(Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){
    //TODO: [ADD CODE HERE]
}

// Only implement the following method for the PAWN (skip for other pieces)
// Method for pawn (only implement for pawn), where pawn reaches end of
// board and must be changed to one of Queen, Rook, Bishop, Knight
void Rook::makeMove(string replacePiece, Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){}


bool Rook::willNextMoveCauseCheck(int newX, int newY){
    //TODO: [ADD CODE HERE]
}

bool Rook::willNextMoveStopCurrentCheck(int newX, int newY){
    //TODO: [ADD CODE HERE]
}

string Rook::getColour() const {
    return colour;
}

int Rook::getX() const {
    return x;
}

int Rook::getY() const {
    return y;
}

Board* Rook::getBoard() const {
    return board;
}

string Rook::getName() const {
    return name;
}

