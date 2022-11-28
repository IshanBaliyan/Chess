
#ifndef COMPUTER_H
#define COMPUTER_H

#include "user.h"
#include "piece.h"
#include <string>


class Computer : public User {
    string name;
    string type;
    Piece*[8][8] board;
    
    public:
        Computer(string name, string type, Piece*[][] board) : name{name}, type{type}, board{board} {}
        string getName() const override;
        string getType() const override;
        string getMove() const override; // Computer returns strategic move
};

#endif

