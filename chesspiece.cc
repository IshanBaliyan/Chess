#include "chesspiece.h"
#include <string>

bool ChessPiece::canMove(int newX, int newY){
    return false;
}

void ChessPiece::makeMove(Piece*& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY){
    return;
}

bool ChessPiece::willNextMoveStopCurrentCheck(int newX, int newY){
    return false;
}

std::string ChessPiece::getColour() const {
    return "";
}

int ChessPiece::getX() const {
    return 0;
}

int ChessPiece::getY() const {
    return 0;
}

BoardModel* ChessPiece::getBoard() const {
    return nullptr;
}

std::string ChessPiece::getName() const {
    return "";
}

