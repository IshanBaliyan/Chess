#include "queen.h"
#include "boardmodel.h"
#include "invalidmoveexception.h"
#include "piece.h"
#include <string>
using namespace std;

Queen::Queen(BoardModel *model, string name, string colour, int x, int y, Piece *comp) : Decorator{comp}, model{model}, name{name}, colour{colour}, x{x}, y{y} {}

int Queen::abs(int x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

bool Queen::canMove(const int newX, const int newY) {
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
    } else if (abs(newX - x) == abs(newY - y)) { // if newpos is diag from currentpos
        if (newX > x) {
            if (newY > y) {
                int j=y+1;
                for (int i=x+1;i<newX;++i) {
                    if (model->getState(i,j) != nullptr) {
                        return false; // return false if there is a piece before destination
                    }
                    ++j;
                }
            } else if (newY < y) {
                int j=y-1;
                for (int i=x+1;i<newX;++i) {
                    if (model->getState(i,j) != nullptr) {
                        return false;
                    }
                    --j;
                }
            }
        } else if (newX < x) {
            if (newY > y) {
                int j=y+1;
                for (int i=x-1;i>newX;--i) {
                    if (model->getState(i,j) != nullptr) {
                        return false;
                    }
                    ++j;
                }
            } else if (newY < y) {
                int j=y-1;
                for (int i=x-1;i>newX;--i) {
                    if (model->getState(i,j) != nullptr) {
                        return false;
                    }
                    --j;
                }
            }
        }
    } else {
        return false;
    }

    if (model->getState(newX,newY) != nullptr &&
            model->getState(newX,newY)->getColour() == colour) {
        return false; // return false if new square is occupied by one of our own pieces
    }

    return true;
}

void Queen::makeMove(Piece *&lastCapturedPiece, Piece *&lastActionPiece, int &lastActionX, int &lastActionY, int newX, int newY) {
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

bool Queen::willNextMoveStopCurrentCheck(int newX, int newY){
    try {
        model->makeMove(x, y, newX, newY);
        model->undo();
        return true;
    } catch (InvalidMoveException &t) {
        return false;
    }
    return false;
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

string Queen::getName() const {
    return name;
}

