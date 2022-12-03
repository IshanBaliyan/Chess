#include "boardmodel.h"
#include "piece.h"
#include "invalidmoveexception.h"

BoardModel::BoardModel(Piece* boardIn[8][8]){
    // Must copy board over manually, since we cannot use MIL with two-dimensional array
    // in current C++ version
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            myBoard[i][j] = boardIn[i][j];
            if(myBoard[i][j]->getColour() == "black"){
                blackPieces.insert(myBoard[i][j]);
            } else{
                whitePieces.insert(myBoard[i][j]);
            }

            // Assign king pointer if the piece is a King
            if(boardIn[i][j]->getName() == "K"){
                if(boardIn[i][j]->getColour() == "black"){
                    blackKing = boardIn[i][j];
                }
                else{
                    whiteKing = boardIn[i][j];
                }
            }
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
    // If black is in check
    if(turn == "black"){
        // Loop through all white's pieces and see if they can strike the king
        for(Piece* whitePiece : whitePieces){
            if(whitePiece->canMove(blackKing->getX(), blackKing->getY()) == true){
                return true;
            }
        }
    }
    // If white is in check
    else{
        // Loop through all black's pieces and see if they can strike the king
        for(Piece* blackPiece : blackPieces){
            if(blackPiece->canMove(whiteKing->getX(), whiteKing->getY())){
                return true;
            }
        }
    }
    return false;
}


bool BoardModel::isCheckmate(){
    // If black needs to see if it is checkmated
    if(turn == "black"){
        // Loop through all black pieces and see if there is anymove that will stop the white's check
        for(Piece* blackPiece : blackPieces){
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(blackPiece->willNextMoveStopCurrentCheck(i, j)){
                        return false;
                    }
                }
            }
        }
    }
    // If white needs to see if it is checkmated
    else{
        // Loop through all white pieces and see if there is anymove that will stop the black's check
        for(Piece* whitePiece : whitePieces){
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(whitePiece->willNextMoveStopCurrentCheck(i, j)){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}


bool BoardModel::isStalemate(){
    // TODO: [INSERT CODE]
}


void BoardModel::addPiece(Piece* piece, int x, int y){
    // If myBoard[x][y] is not a nullptr, delete the piece currently there
    if(myBoard[x][y]){
        deletePiece(myBoard[x][y], x, y);
    }

    // Add the new piece to the set of white or black pieces
    if(piece->getColour() == "black"){
        blackPieces.insert(piece);
    }
    else{
        blackPieces.insert(piece);
    }

    myBoard[x][y] = piece;
}

void BoardModel::removePieceFromBoard(Piece* piece, int x, int y){
    // Remove the piece from the set of black or white pieces
    if(myBoard[x][y]->getColour() == "black"){
        blackPieces.erase(myBoard[x][y]);
    } 
    else{
        whitePieces.erase(myBoard[x][y]);
    }
    // Note, the piece still exists, so make sure to delete it later
}

void BoardModel::deletePiece(Piece* piece, int x, int y){
    // Remove the piece from the set of black or white pieces
    if(myBoard[x][y]->getColour() == "black"){
        blackPieces.erase(myBoard[x][y]);
    } 
    else{
        whitePieces.erase(myBoard[x][y]);
    }

    // Deletes the piece for you
    delete myBoard[x][y];
}

void BoardModel::undo(){
    undo("no special move");
}

void BoardModel::undo(string specialMove){
    if(specialMove == "no special move"){
        // Old position of lastActionPiece will be empty, so just move back
        int capturedX = lastActionPiece->getX();
        int capturedY = lastActionPiece->getY();

        myBoard[lastActionX][lastActionY] = lastActionPiece;
        myBoard[capturedX][capturedY] = lastCapturedPiece;
    }
    else if(specialMove == "castle"){
        // TODO: Add implementation to undo. NOT MVP
    }
    else if(specialMove == "pawn promotion"){
        // TODO: Add implementation to undo. NOT MVP
    }
    else if(specialMove == "en passant"){
        // TODO: Add implementation to undo. NOT MVP
    }
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
