#include "king.h"
#include "boardmodel.h"
#include "invalidmoveexception.h"
#include "piece.h"
#include <string>
using namespace std;

King::King(BoardModel *model, string name, string colour, int x, int y, Piece *comp, bool canCastle) : Decorator{comp}, model{model}, name{name}, colour{colour}, x{x}, y{y}, canCastle{canCastle} {}

int abs(int x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

bool King::canMove(const int newX, const int newY) {
    if (x == newX && y == newY) { // cannot move to the same square it's currently on
        return false;
    } else if (abs(newX - x) == 2 && newY == y) { // if trying to castle (move 2 horizontal)
        if (canCastle) {
            if (newX > x && newX + 1 <= 7) { // if 
                Piece *piece = model->getState(newX+1,y);
                if (piece == nullptr || piece->getName() != "R" || !piece->canCastle()) {
                    return false; // if there's no rook/it can't castle
                }
                for (int i=x+1;i<newX+1;++i) { // check if spaces inbetween are empty
                    if (model->getState(i,y) != nullptr) {
                        return false;
                    }
                }
            } else if (x > newX && newX - 2 >= 0) {
                Piece *piece = model->getState(newX-2,y);
                if (piece == nullptr || piece->getName() != "R" || !piece->canCastle()) {
                    return false; // if there's no rook/it can't castle
                }
                for (int i=newX-1;i<x;++i) { // check if spaces inbetween are empty
                    if (model->getState(i,y) != nullptr) {
                        return false;
                    }
                }
            }
        } else { // if trying to castle, but king has moved (!canCastle()), return false
            return false;
        }
    } else if (abs(newX - x) > 1 || abs(newY - y) > 1) { // if moving more than 1 square
        return false;
    }

    if (model->getState(newX,newY) != nullptr && 
            model->getState(newX,newY)->getColour() == colour) {
        return false; // return false if new square is occupied by one of our own pieces
    }

    return true;
}

void King::makeMove(Piece *&lastCapturedPiece, Piece *&lastActionPiece, int &lastActionX, int &lastActionY, int newX, int newY) {
    if (!canMove(newX, newY)) {
        throw InvalidMoveException{}; // TODO: add params?
    }
    
    if (newX == x + 2 || newX == x - 2) { // if castling
        if (model->isCheck()) { // cannot castle if we are in check
            throw InvalidMoveException{};
        }
        if (newX == x + 2) { // if castling kingside (right side)
            for (int i=x+1;i<=newX;++i) { // make sure no checks while mid-castle
                model->board()[i][y] = model->board()[x][y]; // move king to space
                model->board()[x][y] = nullptr;
                if (model->isCheck()) {
                    model->board()[x][y] = model->board()[i][y]; // revert king back
                    model->board()[i][y] = nullptr;
                    throw InvalidMoveException{};
                }
                model->board()[x][y] = model->board()[i][y]; // revert king back
                model->board()[i][y] = nullptr;
            }
            model->board()[newX-1][y] = model->board()[newX+1][y]; // if no check, move rook
            model->board()[newX+1][y] = nullptr;
            model->board()[newX-1][y]->x = newX-1;
            model->board()[newX-1][y]->canCastle = false;
        } else if (newX == x - 2) { // if castling queenside (left side)
            for (int i=x-1;i>=newX;--i) { // make sure no checks while mid-castle
                model->board()[i][y] = model->board()[x][y]; // move king to space
                model->board()[x][y] = nullptr;
                if (model->isCheck()) {
                    model->board()[x][y] = model->board()[i][y]; // revert king back
                    model->board()[i][y] = nullptr;
                    throw InvalidMoveException{};
                }
                model->board()[x][y] = model->board()[i][y]; // revert king back
                model->board()[i][y] = nullptr;
            }
            model->board()[newX+1][y] = model->board()[newX-2][y]; // if no check, move rook
            model->board()[newX-2][y] = nullptr;
            model->board()[newX+1][y]->x = newX+1;
            model->board()[newX+1][y]->canCastle = false;
        }
        canCastle = false; // king cannot castle again
    }

    // Move king to destination (unless it causes king to be in check)

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

bool King::willNextMoveStopCurrentCheck(int newX, int newY){
    try {
        model->makeMove(x, y, newX, newY);
        model->undo();
        return true;
    } catch (InvalidMoveException &t) {
        return false;
    }
    return false;
}

string King::getColour() const {
    return colour;
}

int King::getX() const {
    return x;
}

int King::getY() const {
    return y;
}

BoardModel *King::getBoard() const {
    return model;
}

string King::getName() const {
    return name;
}

