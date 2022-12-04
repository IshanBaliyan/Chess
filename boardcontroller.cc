#include "boardcontroller.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "boardmodel.h"
#include "boardview.h"
#include "chesspiece.h"
#include "piece.h"
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

Piece *BoardController::createPawn(string colour, int x, int y) {
    model = new BoardModel(pieces);
    Piece *pawn = new Pawn{model->board(), "P", colour, x, y, new ChessPiece};
    return pawn;
}

void BoardController::createDefaultBoard() {

model = new BoardModel(pieces);
// piece = new King{model->board(), pieceName, colour, x, y, new ChessPiece};

// create all of the white pieces
Piece *pawnW1 = createPawn("white", 0,1);
Piece *pawnW2 = createPawn("white", 1,1);
Piece *pawnW3 = createPawn("white", 2,1);
Piece *pawnW4 = createPawn("white", 3,1);
Piece *pawnW5 = createPawn("white", 4,1);
Piece *pawnW6 = createPawn("white", 5,1);
Piece *pawnW7 = createPawn("white", 6,1);
Piece *pawnW8 = createPawn("white", 7,1);

Piece *rookW1 = new Rook{model->board(), "R", "white", 0, 0, new ChessPiece};
Piece *rookW2= new Rook{model->board(), "R", "white", 7, 0, new ChessPiece};

Piece *knightW1 = new Knight{model->board(), "N", "white", 1, 0, new ChessPiece};
Piece *knightW2 = new Knight{model->board(), "N", "white", 6, 0, new ChessPiece};

Piece *bishopW1 = new Bishop{model->board(), "B", "white", 2, 0, new ChessPiece};
Piece *bishopW2 = new Bishop{model->board(), "B", "white", 5, 0, new ChessPiece};

Piece *queenW = new Queen{model->board(), "Q", "white", 3, 0, new ChessPiece};
Piece *kingW = new King{model->board(), "K", "white", 4, 0, new ChessPiece};

// create all black pieces
Piece *pawnB1 = createPawn("black", 0,6);
Piece *pawnB2 = createPawn("black", 1,6);
Piece *pawnB3 = createPawn("black", 2,6);
Piece *pawnB4 = createPawn("black", 3,6);
Piece *pawnB5 = createPawn("black", 4,6);
Piece *pawnB6 = createPawn("black", 5,6);
Piece *pawnB7 = createPawn("black", 6,6);
Piece *pawnB8 = createPawn("black", 7,6);

Piece *rookB1 = new Rook{model->board(), "R", "black", 0, 7, new ChessPiece};
Piece *rookB2= new Rook{model->board(), "R", "black", 7, 7, new ChessPiece};

Piece *knightB1 = new Knight{model->board(), "N", "black", 1, 7, new ChessPiece};
Piece *knightB2 = new Knight{model->board(), "N", "black", 6, 7, new ChessPiece};

Piece *bishopB1 = new Bishop{model->board(), "B", "black", 2, 7, new ChessPiece};
Piece *bishopB2 = new Bishop{model->board(), "B", "black", 5, 7, new ChessPiece};

Piece *queenB = new Queen{model->board(), "Q", "black", 3, 7, new ChessPiece};
Piece *kingB = new King{model->board(), "K", "black", 4, 7, new ChessPiece};

// add pieces to board
model->addPiece(pawnW1, 0, 1);
model->addPiece(pawnW2, 1, 1);
model->addPiece(pawnW3, 2, 1);
model->addPiece(pawnW4, 3, 1);
model->addPiece(pawnW5, 4, 1);
model->addPiece(pawnW6, 5, 1);
model->addPiece(pawnW7, 6, 1);
model->addPiece(pawnW8, 7, 1);

model->addPiece(rookW1, 0, 0);
model->addPiece(knightW1, 1, 0);
model->addPiece(bishopW1, 2, 0);
model->addPiece(queenW, 3, 0);
model->addPiece(kingW, 4, 0);
model->addPiece(bishopW2, 5, 0);
model->addPiece(knightW2, 6, 0);
model->addPiece(rookW2, 7, 0);

model->addPiece(pawnB1, 0, 6);
model->addPiece(pawnB2, 1, 6);
model->addPiece(pawnB3, 2, 6);
model->addPiece(pawnB4, 3, 6);
model->addPiece(pawnB5, 4, 6);
model->addPiece(pawnB6, 5, 6);
model->addPiece(pawnB7, 6, 6);
model->addPiece(pawnB8, 7, 6);

model->addPiece(rookB1, 0, 7);
model->addPiece(knightB1, 1, 7);
model->addPiece(bishopB1, 2, 7);
model->addPiece(queenB, 3, 7);
model->addPiece(kingB, 4, 7);
model->addPiece(bishopB2, 5, 7);
model->addPiece(knightB2, 6, 7);
model->addPiece(rookB2, 7, 7);

// model->addPiece();




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
    createDefaultBoard();
    

    while (true) {
        currLine = getLine();
        if (currLine == "done") {
            bool canExit = true;
            int xCounter = 0;
            int yCounter = 0;

            Piece *piece = model->getState(xCounter, yCounter);

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

            // If conditions are met to finish setup, break out of setup, if not stay in setup mode
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
