#include "knight.h"
#include "boardmodel.h"
#include "invalidmoveexception.h"
#include "piece.h"
#include <string>
using namespace std;

Knight::Knight(BoardModel *model, string name, string colour, int x, int y, Piece *comp) : Decorator{comp}, model{model}, name{name}, colour{colour}, x{x}, y{y} {}

int Knight::abs(int x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

bool Knight::canMove(const int newX, const int newY) {
    if (x == newX || y == newY) {
        return false;
    } else if (abs(newX - x) == 2 && abs(newY - y) == 1) {

    } else if (abs(newX - x) == 1 && abs(newY - y) == 2) {

    } else {
        return false;
    }

    if (model->getState(newX,newY) != nullptr &&
            model->getState(newX,newY)->getColour() == colour) {
        return false; // return false if new square is occupied by one of our own pieces
    }

    return true;
}

void Knight::makeMove(Piece *&lastCapturedPiece, Piece *&lastActionPiece, int &lastActionX, int &lastActionY, int newX, int newY) {
    if (!canMove(newX, newY)) {
        throw InvalidMoveException{}; // TODO: add params?
    }
    Piece *tmpLastCapturedPiece = lastCapturedPiece;
    Piece *tmpLastActionPiece = lastActionPiece;
    int tmpLastActionX = lastActionX;
    int tmpLastActionY = lastActionY;

    lastCapturedPiece = model->board()[newX][newY];
    model->board()[newX][newY] = model->board()[x][y];
    model->board()[x][y] = nullptr;
    lastActionX = x;
    lastActionY = y;
    x = newX;
    y = newY;
    lastActionPiece = this;
    model->removePieceFromBoard(lastCapturedPiece);

    if (model->isCheck()) {
        model->undo();
        lastActionPiece = tmpLastActionPiece;
        lastCapturedPiece = tmpLastCapturedPiece;
        lastActionX = tmpLastActionX;
        lastActionY = tmpLastActionY;
        throw InvalidMoveException{};
    } else {
        model->deletePiece(tmpLastCapturedPiece);
    }
}

bool Knight::willNextMoveStopCurrentCheck(int newX, int newY){
    try {
        model->makeMove(x, y, newX, newY);
        model->undo();
        return true;
    } catch (InvalidMoveException &t) {
        return false;
    }
    return false;
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

string Knight::getName() const {
    return name;
}

