#include "pawn.h"
#include "boardmodel.h"
#include "invalidmoveexception.h"
#include "piece.h"
#include "rook.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include <string>
using namespace std;

Pawn::Pawn(BoardModel *model, string name, string colour, int x, int y, Piece *comp) : Decorator{comp}, model{model}, name{name}, colour{colour}, x{x}, y{y} {}

bool Pawn::canMove(const int newX, const int newY) {
    int vertdistance = 0;
    int startY = 0;

    if (colour == "white") {
        vertdistance = newY - y;
        startY = 1;
    } else if (colour == "black") {
        vertdistance = y - newY;
        startY = 6;
    }

    if (vertdistance == 2 && x == newX) {
        if (y != startY) { // If pawn is not on its starting row, you can't move two squares
            return false;
        } else if (model->getState(newX,newY) != nullptr) { // no capture if 2 space move
            return false;
        }
    } else if (vertdistance != 1) { // can't move more/less than 1 or 2 upwards
        return false;
    } else if (x == newX) {
        if (model->getState(newX,newY) != nullptr) { // if forward move, cannot be capture
            return false;
        }
    } else if (x - newX == 1 || newX - x == 1) { // if diag move, must be a capture
        if (model->getState(newX,newY) == nullptr && 
                *(model->getState(newX,y)) != *(model->enPassantablePiece)) {
            return false;
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

void Pawn::makeMove(Piece *&lastCapturedPiece, Piece *&lastActionPiece, int &lastActionX, int &lastActionY, int newX, int newY) {
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

// Method for pawn (only implement for pawn), where pawn reaches end of
// board and must be changed to one of Queen, Rook, Bishop, Knight
void Pawn::makeMove(string replacePiece, Piece *&lastCapturedPiece, Piece *&lastActionPiece, int &lastActionX, int &lastActionY, int newX, int newY) {
    if (!canMove(newX, newY) || (newY != 7 && newY != 0)) {
        throw InvalidMoveException{}; // TODO: add params?
    }

    if (replacePiece != "R" && replacePiece != "Q" || 
            replacePiece != "N" || replacePiece != "B") {
        throw InvalidMoveException{};
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
        
        Piece *piece = nullptr;
        if (replacePiece == "R") {
            piece = new Rook(model, "R", colour, x, y, comp, false);
        } else if (replacePiece == "Q") {
            piece = new Queen(model, "Q", colour, x, y, comp);
        } else if (replacePiece == "N") {
            piece = new Knight(model, "N", colour, x, y, comp);
        } else if (replacePiece == "B") {
            piece = new Bishop(model, "B", colour, x, y, comp);
        }

        model->removePieceFromBoard(this);
        model->addPiece(piece, piece->getX(), piece->getY());

        lastActionPiece = piece;
    }
}

bool Pawn::willNextMoveStopCurrentCheck(int newX, int newY){
    try {
        model->makeMove(x, y, newX, newY);
        model->undo();
        return true;
    } catch (InvalidMoveException &t) {
        return false;
    }
    return false;
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

BoardModel *Pawn::getBoard() const {
    return model;
}

string Pawn::getName() const {
    return name;
}

