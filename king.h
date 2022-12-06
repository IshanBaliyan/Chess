// king.h
#ifndef _KING_H_
#define _KING_H_
#include "boardmodel.h"
#include "piece.h"
#include "decorator.h"
#include <string>

class King : public Decorator {
    BoardModel *model;
    std::string name;
    std::string colour;
    int x;
    int y;
    bool canCastle;
    bool canMove(const int newX, const int newY);
    public:
        King(BoardModel *model, std::string name, std::string colour, int x, int y, Piece *comp, bool canCastle = true);

        void makeMove(Piece *&lastCapturedPiece, Piece *&lastActionPiece, int &lastActionX, int &lastActionY, int newX, int newY) override;
        bool willNextMoveStopCurrentCheck(int newX, int newY) override;
        std::string getColour() const override;
        int getX() const override;
        int getY() const override;
        BoardModel *getBoard() const override;
        std::string getName() const override;
        bool getCanCastle() const override;
};

#endif
