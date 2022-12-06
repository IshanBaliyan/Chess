
#ifndef HUMAN_H
#define HUMAN_H

#include "user.h"
#include "piece.h"
#include <string>

class Human : public User {
    std::string name;
    std::string type;
    std::string colour;
    Piece* board[8][8];
    
    public:
        Human(std::string type, std::string colour, Piece*board);
        std::string getType() const override;
        std::string getMove() override; // Returns move from cin
        std::string getColour() const override;
};

#endif
