#include "boardmodel.h"
#include "piece.h"
#include "invalidmoveexception.h"

using namespace std;

BoardModel::BoardModel(Piece* boardIn[8][8]){
    // Must copy board over manually, since we cannot use MIL with two-dimensional array
    // in current C++ version
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            myBoard[i][j] = boardIn[i][j];

            // Add each piece to the set of black pieces or set of white pieces for future use
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
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            deletePiece(myBoard[i][j]);
        }
    }
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
            if(checkMove(whitePiece->getX(), whitePiece->getY(), blackKing->getX(), blackKing->getY()) == true){
                return true;
            }
        }
    }
    // If white is in check
    else{
        // Loop through all black's pieces and see if they can strike the king
        for(Piece* blackPiece : blackPieces){
            if(checkMove(blackPiece->getX(), blackPiece->getY(), whiteKing->getX(), whiteKing->getY())){
                return true;
            }
        }
    }
    return false;
}

// Private method
bool BoardModel::willMovingAnywhereCauseACheck(){
    if(turn == "black"){
        // Loop through all black pieces and see if there is any move that will not cause white to check
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
    else{
        // Loop through all white pieces and see if there is any move that will not cause black to check
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

bool BoardModel::isCheckmate(){
    if(!isCheck()){
        // if you are not in check, a checkmate is impossible
        return false;
    }
    return willMovingAnywhereCauseACheck();
}


bool BoardModel::isStalemate(){
    if(isCheck()){
        // if you are in check, a stalemate is impossible
        return false;
    }
    return willMovingAnywhereCauseACheck();
}


void BoardModel::addPiece(Piece* piece, int x, int y){
    // If myBoard[x][y] is not a nullptr, delete the piece currently there
    if(myBoard[x][y]){
        deletePiece(myBoard[x][y]);
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

bool BoardModel::isPieceOnBoard(Piece* piece){
    if(piece->getColour() == "black"){
        // Remove the piece from the black set
        for (auto i = blackPieces.begin(); i != blackPieces.end(); ) {
            if (*i == piece){
                return true;
            }
            else{
                i++;
            }
        }
    } 
    else{
        // Remove the piece from the white set
        for (auto i = whitePieces.begin(); i != whitePieces.end(); ) {
            if (*i == piece){
                return true;
            }
            else{
                i++;
            }
        }
    }
    return false;
}

void BoardModel::removePieceFromBoard(Piece* piece){
    if(piece == nullptr){
        return;
    }
    // Remove the piece from the set of black or white pieces
    if(piece->getColour() == "black"){
        // Remove the piece from the black set
        for (auto i = blackPieces.begin(); i != blackPieces.end(); ) {
            if (*i == piece){
                blackPieces.erase(i);
            }
            else{
                i++;
            }
        }
    } 
    else{
        // Remove the piece from the white set
        for (auto i = whitePieces.begin(); i != whitePieces.end(); ) {
            if (*i == piece){
                whitePieces.erase(i);
            }
            else{
                i++;
            }
        }
    }

    // Set the x,y space on the board to be empty (nullptr means no piece on that square)
    myBoard[piece->getX()][piece->getY()] = nullptr;

    // Note, the piece still exists, so make sure to delete it later
}

void BoardModel::deletePiece(Piece* piece){
    if(piece == nullptr){
        return;
    }

    removePieceFromBoard(piece);

    // Deletes the piece for you
    delete piece;
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

bool BoardModel::checkMove(int currX, int currY, int nextX, int nextY) {
    bool canMove = false;
    try {
        makeMove(currX, currY, nextX, nextY);
        canMove = true;
        undo();
    } catch (InvalidMoveException& t) {
        canMove = false;
    }

    return canMove;
}

Piece* BoardModel::getEnPassantablePiece () const {
    if (enPassantablePiece != nullptr && lastActionPiece != nullptr) {
        if (*enPassantablePiece == *lastActionPiece) {
            return enPassantablePiece;
        }
    }
    return nullptr;
}

void BoardModel::setEnPassantablePiece (Piece* piece) {
    enPassantablePiece = piece;
}
