#include "boardmodel.h"
#include "piece.h"

explicit BoardModel::BoardModel(Piece* boardIn[8][8]){
    // Must copy board over manually, since cannot use MIL with two-dimensional array
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
    // TODO: [INSERT CODE]
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
