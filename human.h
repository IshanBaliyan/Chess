
#ifndef HUMAN_H
#define HUMAN_H

#include "user.h"
#include "piece.h"
#include <string>


class Human : public User {
    string name;
    string type;
    Piece* board[8][8];
    
    public:
        Human(string name, string type, Piece*board);
        string getName() const override;
        string getType() const override;
        string getMove() const override; // Returns move from cin
};

#endif
