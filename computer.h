
#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

#include "piece.h"
#include "user.h"

class Computer : public User {
   private:
    string name;
    string type;
    Piece* board[8][8];
    string getRandomMove();

   public:
    Computer(string name, string type, Piece* board);
    string getName() const override;
    string getType() const override;
    string getMove() const override;  // Computer returns strategic move
};

#endif
