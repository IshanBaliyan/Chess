
#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <vector>

#include "piece.h"
#include "user.h"

class Computer : public User {
   private:
    string name;
    string type;
    string colour;
    int level;
    Piece* board[8][8];
    vector<Piece*> blackPieces;
    vector<Piece*> whitePieces;         // list of pices on board
    vector<pair<int, int>> movesList;  // list of possible moves for a piece

    Piece* getRandPiece();
    void addToMoveList(int x, int y);
    void findPossibleMoves(Piece *piece); // add all possible moves for piece to moveLists
    string convertMove(int x, int y) ;  // converts x y coordinates to a move (eg. 0 ,0 => "a1")
    string getRandomMove();
    

   public:
    Computer(string name, string type, string colour, int level, Piece* boardIn[8][8]);
    string getType() const override;
    string getMove() override;  // Computer returns strategic move
    string getColour() const;
    int getLevel() const;
};

#endif
