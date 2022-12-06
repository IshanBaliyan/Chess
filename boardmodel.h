
// boardmodel.h

#ifndef BOARDMODEL_H
#define BOARDMODEL_H
#include <string>
#include <set>
#include "subject.h"

class Piece;

class BoardModel : public Subject {
  Piece*** myBoard; // Really means Piece*[][], two-dimensional array
  std::string turn;
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

  // Variable to handle en passant
  Piece* enPassantablePiece;

  bool willMovingAnywhereCauseACheck();

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
  void deletePiece(Piece* piece); // removes piece from board and deletes it
  bool isPieceOnBoard(Piece* piece);
  void removePieceFromBoard(Piece* piece); // removes piece from board, but it still exists
  void undo();
  void undo(std::string specialMove);
  void changeTurn(std::string colour);
  std::string getTurn() const;
  void nextTurn(); // Forward to next black/white player's turn
  void makeMove(int currentX, int currentY, int newX, int newY); // Throws error if the move is not possible
  void makeMoveWithPawnPromotion(std::string replacePiece,int currentX, int currentY, int newX, int newY);
  bool checkMove(int currX, int currY, int nextX, int nextY);  // checks if piece is able to move to x, y position
  Piece* getEnPassantablePiece() const;
  void setEnPassantablePiece(Piece* piece);
  bool pieceEqualsOtherPiece(Piece* pieceOne, Piece* pieceTwo) const; // check if two pieces are equal
};

#endif

