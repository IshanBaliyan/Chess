#include "boardmodel.h"
#include "piece.h"

void BoardModel::display(){
    notifyObservers();
}


BoardModel::~Board(){
    delete board;
}

Piece* BoardModel::getState(int x, int y) const {
    return board[x][y];
}


bool BoardModel::isCheck(){
    //TODO: [INSERT CODE]
}


bool BoardModel::isCheckmate(){
    //TODO: [INSERT CODE]
}


bool BoardModel::isStalemate(){
    //TODO: [INSERT CODE]
}


void BoardModel::addPiece(Piece* piece, int x, int y){
    //TODO: [INSERT CODE]
}

void BoardModel::removePiece(Piece* piece, int x, int y){
    //TODO: [INSERT CODE]
}

void BoardModel::undo(){
    //TODO: [INSERT CODE]
}

void BoardModel::undo(string specialMove){
    //TODO: [INSERT CODE]
}

void BoardModel::changeColour(string colour){
    //TODO: [INSERT CODE]
}

