// boardcontrolller.h

#ifndef _BOARDCONTROLLER_H_
#define _BOARDCONTROLLER_H_
#include <string>

#include "boardmodel.h"

// BoardController class handles all input, output (through ModelView class) and runs the whole application
class BoardController {
    BoardModel *model;

   private:
    string whitePlayer;
    string blackPlayer;
    bool changedStartColour;
    float whiteScore;
    float blackScore;
    Piece *pieces[8][8];

    int parseX(string coords);  // converts column letter of position (ie "e" in e1) into numerical equivalent
    int parseY(string coors);
    string getLine();
    string getColour(string inputName);    // gets the colour of the piece from the inputted piece name
    string convertName(string inputName);  // converts inputted piece name to standard used in program
    void createDefaultBoard();
    Piece *createPawn(string colour, int x, int y);
    bool checkForPawnPromotion(BoardModel *model);  // checks whole board if a pawn currently is in promotion square
    bool willPawnPromoteOnMove(Piece *piece);       // checks if piece is a pawn that will be promoted on move
    void updateScore();
    bool containsTwoKings();  // checks if board contains exactly two kings (one black and one white)
    int getComputerLevel(string player);

   public:
    BoardController();
    void setWhitePlayer(string player);
    void setBlackPlayer(string player);
    string getWhitePlayer();
    string getBlackPlayer();
    void initializeScores();  // sets score of black and white to 0

    void resetGame();
    void setupGame();
    void runGame();
    void outputWins();
};

#endif
