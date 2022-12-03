
// boardmodel.h

#ifndef BOARDMODEL_H
#define BOARDMODEL_H
#include <string>
#include "subject.h"

using namespace std;

class Piece;

class BoardModel : public Subject {
  Piece*** myBoard; // Really means Piece[][], two-dimensional array
  string turn;

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
  void removePiece(Piece* piece, int x, int y);
  void undo();
  void undo(string specialMove);
  void changeTurn(string colour);
  string getTurn() const;
  void nextTurn(); // Forward to next black/white player's turn
};

#endif

