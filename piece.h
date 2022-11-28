#ifndef PIECE_H
#define PIECE_H
#include <string>

class Board{} // forward declaration

class Piece {
    public:
        virtual ~Piece();
        virtual void makeMove(Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY) = 0;
        virtual void makeMove(string replacePiece, Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY) = 0;
        virtual bool willNextMoveCauseCheck(int newX, int newY) = 0;
        virtual bool willNextMoveStopCurrentCheck(int newX, int newY) = 0;
        virtual string getColour() const = 0;
        virtual int getX() const = 0;
        virtual int getY() const = 0;
        virtual Board* getBoard() const = 0;
        virtual string getName() const = 0;
}

