
// king.h
#ifndef _KING_H_
#define _KING_H_
#include "piece.h"
#include "decorator.h"
#include <string>

class King : public Decorator {
    Board* board;
    string name;
    string colour;
    int x;
    int y;
    public:
        King(Board* board, string name, string colour, int x, int y, Piece *comp);

        void makeMove(Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY) override;
        void makeMove(string replacePiece, Piece& lastCapturedPiece, Piece*& lastActionPiece, int& lastActionX, int& lastActionY, int newX, int newY) override;
        bool willNextMoveCauseCheck(int newX, int newY) override;
        bool willNextMoveStopCurrentCheck(int newX, int newY) override;
        string getColour() const override;
        int getX() const override;
        int getY() const override;
        Board* getBoard() const override;
        string getName() const override;
};

#endif

