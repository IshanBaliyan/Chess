#ifndef _PIECE_H_
#define _PIECE_H_
#include "boardmodel.h"
#include <string>

class Piece { 
    public:
        virtual ~Piece();
        virtual bool canMove(const int newX, const int newY) = 0;
        virtual void makeMove(Piece *&lastCapturedPiece, Piece *&lastActionPiece, int &lastActionX, int &lastActionY, int newX, int newY) = 0;
        virtual void makeMove(std::string replacePiece, Piece *&lastCapturedPiece, Piece *&lastActionPiece, int &lastActionX, int &lastActionY, int newX, int newY);
        virtual bool willNextMoveStopCurrentCheck(int newX, int newY) = 0;
        virtual std::string getColour() const = 0;
        virtual int getX() const = 0;
        virtual int getY() const = 0;
        virtual std::string getName() const = 0;
        virtual bool getCanCastle() const;
};

#endif
