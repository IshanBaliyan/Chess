#include "piece.h"
#include "invalidmoveexception.h"
#include <string>
using namespace std;

void Piece::makeMove(string replacePiece, Piece *&lastCapturedPiece, Piece *&lastActionPiece, int &lastActionX, int &lastActionY, int newX, int newY) {
    throw InvalidMoveException{};
}

bool Piece::getCanCastle() const {
    return false;
}

Piece::~Piece() {}
