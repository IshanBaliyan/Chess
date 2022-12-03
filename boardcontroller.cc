#include "boardcontroller.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "boardmodel.h"
#include "boardview.h"
#include "chesspiece.h"
#include "computer.h"
#include "human.h"
#include "user.h"
using namespace std;

int BoardController::parseX(string coords) {
    int x;
    map<char, int> xMap;

    xMap['a'] = 0;
    xMap['b'] = 1;
    xMap['c'] = 2;
    xMap['d'] = 3;
    xMap['e'] = 4;
    xMap['f'] = 5;
    xMap['g'] = 6;
    xMap['h'] = 7;

    x = xMap[coords[0]];

    return x;
}

int BoardController::parseX(string coords) {
    int y;
    map<char, int> yMap;

    yMap['1'] = 0;
    yMap['2'] = 1;
    yMap['3'] = 2;
    yMap['4'] = 3;
    yMap['5'] = 4;
    yMap['6'] = 5;
    yMap['7'] = 6;
    yMap['8'] = 7;

    y = yMap[coords[1]];

    return y;
}

string BoardController::getLine() {
    string currIn;
    getline(cin, currIn);

    return currIn;
}

string BoardController::convertName(string inputName) {
    string newName;
    char temp;
    if (islower(inputName[0])) {
        temp = inputName[0];
        temp = temp - 'a' + 'A';  // convert to capital
        newName = string(1, temp);
        return newName;
    }
    return inputName;
}

string BoardController::getColour(string inputName) {
    if (islower(inputName[0])) {
        return "black";
    } else {
        return "white";
    }
}

// PUBLIC FUNCTIONS

void BoardController::setWhitePlayer(string player) {
    whitePlayer = player;
}

void BoardController::setBlackPlayer(string player) {
    blackPlayer = player;
}

string BoardController::getWhitePlayer() {
    return whitePlayer;
}

string BoardController::getBlackPlayer() {
    return blackPlayer;
}

void BoardController::resetGame() {
    // TODO: INSERT CODE
    // add new board
    changedStartColour = false;
}

void BoardController::setupGame() {
    // TODO: INSERT CODE
    string currLine;
    string command;
    string coord;
    int x;
    int y;
    string pieceName;
    string colour;

    // TODO: create boardmodel

    while (true) {
        currLine = getLine();
        if (currLine == "done") {
            bool canExit = true;
            int xCounter = 0;
            int yCounter = 0;

            Piece *piece = model->board()->getState(xCounter, yCounter);

            while (xCounter < 8) {  // check for any black pawns on first row (x, 0)

                if (piece->getName() == "P") {
                    if (piece->getColour() == "black") {
                        cout << "Cannot have black pawn at " << xCounter << ", " << yCounter << endl;
                        canExit = false;
                    }
                }
                xCounter++;
            }

            yCounter = 7;
            xCounter = 0;
            while (xCounter < 8) {
                if (piece->getName() == "P") {
                    if (piece->getColour() == "white") {
                        cout << "Cannot have whtie pawn at " << xCounter << ", " << yCounter << endl;
                        canExit = false;
                    }
                }
            }

            // Check if king is in check
            if (model->isCheck()) {
                cout << "king is in check" << endl;
                canExit = false;
            }

            // If conditions are met to finish setup, break out of setup, if not continue
            if (canExit) {
                break;
            } else {
                continue;
            }

        } else {
            istringstream ss1{currLine};
            ss1 >> command;

            if (command == "+") {
                ss1 >> pieceName;
                ss1 >> coord;

                colour = getColour(pieceName);
                pieceName = convertName(pieceName);

                // convert position to corresponding x and y
                x = parseX(coord);
                y = parseY(coord);

                Piece *piece;

                if (pieceName == "K") {
                    piece = new King{model->board(), pieceName, colour, x, y, new ChessPiece};
                } else if (pieceName == "Q") {
                    piece = new Bishop{model->board(), pieceName, colour, x, y, new ChessPiece};
                } else if (pieceName == "B") {
                    piece = new Bishop{model->board(), pieceName, colour, x, y, new ChessPiece};
                } else if (pieceName == "R") {
                    piece = new Bishop{model->board(), pieceName, colour, x, y, new ChessPiece};

                } else if (pieceName == "N") {
                    piece = new Bishop{model->board(), pieceName, colour, x, y, new ChessPiece};

                } else if (pieceName == "P") {
                    piece = new Bishop{model->board(), pieceName, colour, x, y, new ChessPiece};
                }

                model->addPiece(piece, x, y);

            } else if (command == "-") {
                ss1 >> coord;

                x = parseX(coord);
                y = parseY(coord);

                model->removePiece(model->board()->getPiece(x, y)), x, y);

            } else if (command == "=") {
                ss1 >> colour;

                if (colour == "black") {
                    currTurn = "black";
                } else {
                    currTurn = "white";
                }

                changedStartColour = true;
            }
        }
    }
}

void BoardController::runGame() {
    // TODO: INSERT CODE

    bool isRunning = true;
    string currLine;
    string command;
    string currCoord;  // current coordinate of piece
    string nextCoord;  // coordinate to move piece to
    int x1;
    int y1;
    int x2;
    int y2;
    string piece;

    while (isRunning) {
        currLine = getLine();

        istringstream ss1{currLine};
        ss1 >> command;

        if (command == "move") {
            ss1 >> currCoord;

            ss1 >> nextCoord;

            // TODO: check pawn promotion

            // if normal move:
            x1 = parseX(currCoord);
            y1 = parseY(currCoord);

            x2 = parseX(nextCoord);
            y2 = parseY(nextCoord);

            // TODO: check castling

        } else if (command == "resign") {
            if (currTurn == "white") {
                blackScore++;
            } else {
                whiteScore++;
            }

            isRunning = false;
        }
    }
}

void BoardController::outputWins() {
    // TODO: INSERT CODE
}
