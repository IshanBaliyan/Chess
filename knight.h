// knight.h
#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "piece.h"
#include "decorator.h"
#include <string>

class Knight : public Decorator {
    BoardModel *model;
    std::string name;
    std::string colour;
    int x;
    int y;
    bool canMove(const int newX, const int newY);
    public:
        Knight(BoardModel *model, std::string name, std::string colour, int x, int y, Piece *comp);

        void makeMove(Piece *&lastCapturedPiece, Piece *&lastActionPiece, int &lastActionX, int &lastActionY, int newX, int newY) override;
        bool willNextMoveStopCurrentCheck(int newX, int newY) override;
        std::string getColour() const override;
        int getX() const override;
        int getY() const override;
        BoardModel *getBoard() const override;
        std::string getName() const override;
};

#endif
