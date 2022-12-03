
// boardmodel.h

#ifndef BOARDMODEL_H
#define BOARDMODEL_H
#include <string>
#include <set>
#include "subject.h"

using namespace std;

class Piece;

class BoardModel : public Subject {
  Piece*** myBoard; // Really means Piece*[][], two-dimensional array
  string turn;
  set<Piece*> blackPieces;
  set<Piece*> whitePieces;

  // Need for finding check, checkmate, stalemate
  Piece *whiteKing;
  Piece *blackKing;

  // Variables to undo last move
  Piece* lastCapturedPiece;
  Piece* lastActionPiece;
  int lastActionX;
  int lastActionY;
  
 public:
  explicit BoardModel(Piece* boardIn[8][8]);

  // Returns Piece*[][], but formatted as Piece*** for C++ constraints
  Piece*** &board() { return myBoard; }
  void display(); // Notify observers, which display to user
  ~BoardModel();
  Piece* getState(int x, int y) const override; // Piece at given x and y position on board

  bool isCheck();
  bool isCheckmate();
  bool isStalemate();
  void addPiece(Piece* piece, int x, int y);
  void deletePiece(Piece* piece, int x, int y); // removes piece from board and deletes it
  void removePieceFromBoard(Piece* piece, int x, int y); // removes piece from board, but it still exists
  void undo();
  void undo(string specialMove);
  void changeTurn(string colour);
  string getTurn() const;
  void nextTurn(); // Forward to next black/white player's turn
  void makeMove(int currentX, int currentY, int newX, int newY); // Throws error if the move is not possible
  void makeMoveWithPawnPromotion(string replacePiece,int currentX, int currentY, int newX, int newY);
};

#endif

