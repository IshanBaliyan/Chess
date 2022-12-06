
#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <vector>

#include "piece.h"
#include "user.h"

class Computer : public User {
   private:
    std::string name;
    std::string type;
    std::string colour;
    int level;
    Piece* board[8][8];
    vector<Piece*> blackPieces;
    vector<Piece*> whitePieces;        // list of pices on board
    vector<pair<int, int>> movesList;  // list of possible moves for a piece

    Piece* getRandPiece();
    void addToMoveList(int x, int y);
    void findPossibleMoves(Piece* piece);                        // add all possible moves for piece to moveLists
    std::string convertMove(int x, int y);                            // converts x y coordinates to a move (eg. 0 ,0 => "a1")
    std::string getRandomMove();
    int getLevel();

   public:
    Computer(std::string type, std::string colour, Piece* boardIn[8][8]);
    std::string getType() const override;
    std::string getMove() override;  // Computer returns strategic move
    std::string getColour() const override;
};

#endif
