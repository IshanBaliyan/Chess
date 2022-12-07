// boardcontrolller.h

#ifndef _BOARDCONTROLLER_H_
#define _BOARDCONTROLLER_H_
#include <string>

#include "boardmodel.h"

// BoardController class handles all input, output (through ModelView class) and runs the whole application
class BoardController {
    BoardModel *model;

   private:
    std::string whitePlayer;
    std::string blackPlayer;
    bool changedStartColour;
    float whiteScore;
    float blackScore;
    Piece *pieces[8][8];
    bool usedSetup = false;

    int parseX(std::string coords);  // converts column letter of position (ie "e" in e1) into numerical equivalent
    int parseY(std::string coors);
    std::string getLine();
    std::string getColour(std::string inputName);    // gets the colour of the piece from the inputted piece name
    std::string convertName(std::string inputName);  // converts inputted piece name to standard used in program
    void createDefaultBoard();
    Piece *createPawn(std::string colour, int x, int y);
    bool checkForPawnPromotion(BoardModel *model);  // checks whole board if a pawn currently is in promotion square
    bool willPawnPromoteOnMove(Piece *piece);       // checks if piece is a pawn that will be promoted on move
    void updateScore();
    bool containsTwoKings();  // checks if board contains exactly two kings (one black and one white)
    int getComputerLevel(std::string player);

   public:
    BoardController(){};
    void setWhitePlayer(std::string player);
    void setBlackPlayer(std::string player);
    std::string getWhitePlayer();
    std::string getBlackPlayer();
    void initializeScores();  // sets score of black and white to 0

    void resetGame();
    void setupGame();
    void runGame();
    void outputWins();
};

#endif
