
// boardmodel.h

#ifndef BOARDMODEL_H
#define BOARDMODEL_H
#include <string>
#include "subject.h"

class Piece;

class BoardModel : public Subject {
  Piece* board[8][8];

 public:
  explicit Board(Piece* board[8][8]): board{board} {}

  Piece*[][] *&board() { return board; }
  void display(); // Notify observers, which display to user
  ~Board();
  Piece* getState(int x, int y) const override; // Piece at given x and y position on board

  bool isCheck();
  bool isCheckmate();
  bool isStalemate();
  void addPiece(Piece* piece, int x, int y);
  void removePiece(Piece* piece, int x, int y);
  void undo();
  void undo(string specialMove);
  void changeColour(string colour);
};

#endif

