#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "boardcontroller.h"

int main() {
    // TODO: [Create boardcontroller to handle almost the entire program]

    string currLine;
    string command;
    string whitePlayer;
    string blackPlayer;

    while (getline(cin, currLine)) {
        BoardController* boardController = new BoardController{};

        boardController->initializeScores();

        if (cin.eof()) {
            boardController->outputWins();
            break;
        }

        istringstream ss1{currLine};
        ss1 >> command;

        if (command == "game") {
            cout << "entered game" << endl;  // remove later

            ss1 >> whitePlayer;
            ss1 >> blackPlayer;
            boardController->setWhitePlayer(whitePlayer);
            boardController->setBlackPlayer(blackPlayer);

            boardController->runGame();

        } else if (command == "setup") {
            cout << "entered setup" << endl;  // remove later

            boardController->setupGame();
        }
    }

    return 0;
}
