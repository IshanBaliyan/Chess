// boardcontrolller.h

#ifndef _BOARDCONTROLLER_H_
#define _BOARDCONTROLLER_H_
#include "boardmodel.h"
#include <string>

// BoardController class handles all input, output (through ModelView class) and runs the whole application
class BoardController {
    BoardModel* model;
    public:
        void resetGame();
        void setupGame();
        void runGame();
        void outputWins();
}




