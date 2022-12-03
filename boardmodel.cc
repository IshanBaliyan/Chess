#include "boardmodel.h"
#include "piece.h"
#include "invalidmoveexception.h"

BoardModel::BoardModel(Piece* boardIn[8][8]){
    // Must copy board over manually, since we cannot use MIL with two-dimensional array
    // in current C++ version
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            myBoard[i][j] = boardIn[i][j];
        }
    }
}

void BoardModel::display(){
    notifyObservers();
}


BoardModel::~BoardModel(){
    delete myBoard;
}

Piece* BoardModel::getState(int x, int y) const {
    return myBoard[x][y];
}


bool BoardModel::isCheck(){
    // TODO: [INSERT CODE]
}


bool BoardModel::isCheckmate(){
    // TODO: Call isCheck() constantly, while trying to run canMove() for every possible permutation of
    // pieces on the board
}


bool BoardModel::isStalemate(){
    // TODO: [INSERT CODE]
}


void BoardModel::addPiece(Piece* piece, int x, int y){
    // If myBoard[x][y] is not a nullptr, delete the piece currently there
    if(myBoard[x][y]){
        delete myBoard[x][y];
    }
    myBoard[x][y] = piece;
}

void BoardModel::removePiece(Piece* piece, int x, int y){
    delete myBoard[x][y];
}

void BoardModel::undo(){
    // TODO: [INSERT CODE]
}

void BoardModel::undo(string specialMove){
    // TODO: [INSERT CODE]
}

void BoardModel::changeTurn(string colour){
    turn = colour;
}

string BoardModel::getTurn() const {
    return turn;
}

void BoardModel::nextTurn() {
    // next turn
    if(turn == "black"){
      turn = "white";
    } else{
      turn = "black";
    }
}

void BoardModel::makeMove(int currentX, int currentY, int newX, int newY){
    try{
        myBoard[currentX][currentY]->makeMove(lastCapturedPiece, lastActionPiece, lastActionX, lastActionY,
        newX, newY);
    } catch (InvalidMoveException& t){
        throw;
    }

}

void BoardModel::makeMoveWithPawnPromotion(string replacePiece,int currentX, int currentY, int newX, int newY){
    try{
        myBoard[currentX][currentY]->makeMove(replacePiece, lastCapturedPiece, lastActionPiece, lastActionX, 
        lastActionY, newX, newY);
    } catch (InvalidMoveException& t){
        throw;
    }
}
