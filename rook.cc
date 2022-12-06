#include "rook.h"
#include "piece.h"
#include <string>
using namespace std;

Rook::Rook(BoardModel *model, string name, string colour, int x, int y, Piece *comp, bool canCastle) : Decorator{comp}, model{model}, name{name}, colour{colour}, x{x}, y{y}, canCastle{canCastle} {}

bool Rook::canMove(const int newX, const int newY) {
    if (x == newX && y == newY) {
        return false;
    } else if (newX == x) { // if newpos is vertical from currentpos
        if (newY > y) {
            for (int i=y+1;i<newY;++i) {
                if (model->getState(x,i) != nullptr) {
                    return false;
                }
            }
        } else if (newY < y) {
            for (int i=y-1;i>newY;--i) {
                if (model->getState(x,i) != nullptr) {
                    return false;
                }
            }
        }
    } else if (newY == y) { // if newpos is horizontal from currentpos
        if (newX > x) {
            for (int i=x+1;i<newX;++i) {
                if (model->getState(i,y) != nullptr) {
                    return false;
                }
            }
        } else if (newX < x) {
            for (int i=x-1;i>newX;--i) {
                if (model->getState(i,y) != nullptr) {
                    return false;
                }
            }
        }
    } else {
        return false;
    }

    if (model->getState(newX,newY) != nullptr &&
            ((model->getState(newX,newY)->colour == "black" && colour == "black") ||
            (model->getState(newX,newY)->colour == "white" && colour == "white"))) {
        return false; // return false if new square is occupied by one of our own pieces
    }

    return true;
}

void Rook::makeMove(Piece *&lastCapturedPiece, Piece *&lastActionPiece, int &lastActionX, int &lastActionY, int newX, int newY) {
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
        canCastle = false;
    }
}

bool Rook::willNextMoveStopCurrentCheck(int newX, int newY){
    try {
        makeMove(model->lastCapturedPiece, model->lastActionPiece, 
                model->lastActionX, model->lastActionY, newX, newY);
        model->undo();
        return true;
    } catch (InvalidMoveException &t) {
        return false;
    }
    return false;
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

BoardModel *Rook::getBoard() const {
    return model;
}

string Rook::getName() const {
    return name;
}

