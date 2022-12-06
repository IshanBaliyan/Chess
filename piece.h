#ifndef _PIECE_H_
#define _PIECE_H_
#include "boardmodel.h"
#include <string>


class Piece {
        virtual bool canMove(int newX, int newY) = 0;
    public:
        virtual ~Piece();
        virtual void makeMove(Piece *&lastCapturedPiece, Piece *&lastActionPiece, int &lastActionX, int &lastActionY, int newX, int newY) = 0;
        virtual bool willNextMoveStopCurrentCheck(int newX, int newY) = 0;
        virtual string getColour() const = 0;
        virtual int getX() const = 0;
        virtual int getY() const = 0;
        virtual BoardModel *getBoard() const = 0;
        virtual std::string getName() const = 0;
};

#endif
