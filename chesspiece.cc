#include "chesspiece.h"
#include <string>

void ChessPiece::makeMove(Piece*& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){
    return;
}

// Only implement the following method for the PAWN (skip for other pieces)
// Method for pawn (only implement for pawn), where pawn reaches end of
// board and must be changed to one of Queen, Rook, Bishop, Knight
void ChessPiece::makeMove(string replacePiece, Piece*& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){}


bool ChessPiece::willNextMoveCauseCheck(int newX, int newY){
    return false;
}

bool ChessPiece::willNextMoveStopCurrentCheck(int newX, int newY){
    return false;
}

string ChessPiece::getColour() const {
    return "";
}

int ChessPiece::getX() const {
    return 0;
}

int ChessPiece::getY() const {
    return 0;
}

Board* ChessPiece::getBoard() const {
    return nullptr;
}

string ChessPiece::getName() const {
    return "";
}

