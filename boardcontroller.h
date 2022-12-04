// boardcontrolller.h

#ifndef _BOARDCONTROLLER_H_
#define _BOARDCONTROLLER_H_
#include <string>

#include "boardmodel.h"

// BoardController class handles all input, output (through ModelView class) and runs the whole application
class BoardController {
    BoardModel* model;

   private:
    string currTurn;
    string whitePlayer;
    string blackPlayer;
    bool changedStartColour;
    int whiteScore;
    int blackScore;
    Piece* pieces[8][8]; 

    int parseX(string coords);  // converts column letter of position (ie "e" in e1) into numerical equivalent
    int parseY(string coors);
    string getLine();
    string getColour(string inputName); // gets the colour of the piece from the inputted piece name
    string convertName(string inputName); // converts inputted piece name to standard used in program
    void createDefaultBoard();
    Piece *createPawn(string colour, int x, int y);

   public:
    BoardController();
    void setWhitePlayer(string player);
    void setBlackPlayer(string player);
    string getWhitePlayer();
    string getBlackPlayer();
    
    void resetGame();
    void setupGame();
    void runGame();
    void outputWins();
};

#endif
