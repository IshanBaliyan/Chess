#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include "piece.h"
#include <iostream>

class ChessPiece: public Piece { 
 public:
        bool canMove(int newX, int newY) override;
        void makeMove(Piece*& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY) override;
        bool willNextMoveStopCurrentCheck(int newX, int newY) override;
        std::string getColour() const override;
        int getX() const override;
        int getY() const override;
        void setX(int newX) override;
        void setY(int newY) override;
        std::string getName() const override;
};

#endif

