#include "pawn.h"
#include "piece.h"
#include <string>

Pawn::Pawn(Board* board, string name, string colour, int x, int y, Piece *comp) : Decorator{comp}, board{board}, name{name}, colour{colour}, x{x}, y{y} {}

void Pawn::makeMove(Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){
    //TODO: [ADD CODE HERE]
}

// Only implement the following method for the PAWN (skip for other pieces)
// Method for pawn (only implement for pawn), where pawn reaches end of
// board and must be changed to one of Queen, Rook, Bishop, Knight
void Pawn::makeMove(string replacePiece, Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){}


bool Pawn::willNextMoveCauseCheck(int newX, int newY){
    //TODO: [ADD CODE HERE]
}

bool Pawn::willNextMoveStopCurrentCheck(int newX, int newY){
    //TODO: [ADD CODE HERE]
}

string Pawn::getColour() const {
    return colour;
}

int Pawn::getX() const {
    return x;
}

int Pawn::getY() const {
    return y;
}

Board* Pawn::getBoard() const {
    return board;
}

string Pawn::getName() const {
    return name;
}

