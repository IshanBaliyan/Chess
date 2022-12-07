#include "boardcontroller.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "bishop.h"
#include "boardmodel.h"
#include "boardview.h"
#include "chesspiece.h"
#include "computer.h"
#include "human.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "piece.h"
#include "queen.h"
#include "rook.h"
#include "user.h"
#include "invalidmoveexception.h"

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

int BoardController::parseY(string coords) {
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

bool BoardController::checkForPawnPromotion(BoardModel *model) {
    int xPosition = 0;
    int yPosition = 0;
    Piece *piece;

    while (xPosition < 8) {  // check for any black pawns on first row (x, 0)
        piece = model->getState(xPosition, yPosition);

        if (piece->getName() == "P") {
            if (piece->getColour() == "black") {
                return true;
            }
        }
        xPosition++;
    }

    yPosition = 7;
    xPosition = 0;
    while (xPosition < 8) {
        piece = model->getState(xPosition, yPosition);
        if (piece->getName() == "P") {
            if (piece->getColour() == "white") {
                cout << "Cannot have whtie pawn at " << xPosition << ", " << yPosition << endl;
                return true;
            }
        }
        xPosition++;
    }
    return false;
}

bool BoardController::willPawnPromoteOnMove(Piece *piece) {
    if(piece == nullptr){
        return false;
    }
    if (piece->getName() == "P") {
        if (piece->getY() == 6) {
            if (piece->getColour() == "white") {
                return true;
            }
        }

        if (piece->getY() == 1) {
            if (piece->getColour() == "black") {
                return true;
            }
        }
    }
    return false;
}

void BoardController::updateScore() {
    if (model->getTurn() == "white") {
        blackScore++;
    } else {
        whiteScore++;
    }
}

bool BoardController::containsTwoKings() {
    Piece *piece;
    int numKingW = 0;
    int numKingB = 0;

    for (int i = 0; i <= 7; i++) {  // loop over row
        for (int j = 0; j <= 7; j++) {
            piece = model->getState(i, j);
            if(piece == nullptr){
                continue;
            }
            if (piece->getName() == "K") {
                if (piece->getColour() == "white") {
                    numKingW++;
                } else if (piece->getColour() == "black") {
                    numKingB++;
                }
            }
        }
    }

    if (numKingW == 1 && numKingB == 1) {
        return true;
    }

    return false;
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

int BoardController::getComputerLevel(string player) {
    char level = player[9];
    int levelNum = level - '0';
    return levelNum;

}

Piece *BoardController::createPawn(string colour, int x, int y) {
    Piece *pawn = new Pawn{model, "P", colour, x, y, new ChessPiece};
    return pawn;
}

void BoardController::initializeScores() {
    whiteScore = 0;
    blackScore = 0;
}

void BoardController::createDefaultBoard() {

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            pieces[i][j] = nullptr;
        }
    }

    model = new BoardModel(pieces);

    // create all of the white pieces
    Piece *pawnW1 = createPawn("white", 0, 1);
    Piece *pawnW2 = createPawn("white", 1, 1);
    Piece *pawnW3 = createPawn("white", 2, 1);
    Piece *pawnW4 = createPawn("white", 3, 1);
    Piece *pawnW5 = createPawn("white", 4, 1);
    Piece *pawnW6 = createPawn("white", 5, 1);
    Piece *pawnW7 = createPawn("white", 6, 1);
    Piece *pawnW8 = createPawn("white", 7, 1);

    Piece *rookW1 = new Rook{model, "R", "white", 0, 0, new ChessPiece};
    Piece *rookW2 = new Rook{model, "R", "white", 7, 0, new ChessPiece};

    Piece *knightW1 = new Knight{model, "N", "white", 1, 0, new ChessPiece};
    Piece *knightW2 = new Knight{model, "N", "white", 6, 0, new ChessPiece};

    Piece *bishopW1 = new Bishop{model, "B", "white", 2, 0, new ChessPiece};
    Piece *bishopW2 = new Bishop{model, "B", "white", 5, 0, new ChessPiece};

    Piece *queenW = new Queen{model, "Q", "white", 3, 0, new ChessPiece};
    Piece *kingW = new King{model, "K", "white", 4, 0, new ChessPiece};

    // create all black pieces
    Piece *pawnB1 = createPawn("black", 0, 6);
    Piece *pawnB2 = createPawn("black", 1, 6);
    Piece *pawnB3 = createPawn("black", 2, 6);
    Piece *pawnB4 = createPawn("black", 3, 6);
    Piece *pawnB5 = createPawn("black", 4, 6);
    Piece *pawnB6 = createPawn("black", 5, 6);
    Piece *pawnB7 = createPawn("black", 6, 6);
    Piece *pawnB8 = createPawn("black", 7, 6);

    Piece *rookB1 = new Rook{model, "R", "black", 0, 7, new ChessPiece};
    Piece *rookB2 = new Rook{model, "R", "black", 7, 7, new ChessPiece};

    Piece *knightB1 = new Knight{model, "N", "black", 1, 7, new ChessPiece};
    Piece *knightB2 = new Knight{model, "N", "black", 6, 7, new ChessPiece};

    Piece *bishopB1 = new Bishop{model, "B", "black", 2, 7, new ChessPiece};
    Piece *bishopB2 = new Bishop{model, "B", "black", 5, 7, new ChessPiece};

    Piece *queenB = new Queen{model, "Q", "black", 3, 7, new ChessPiece};
    Piece *kingB = new King{model, "K", "black", 4, 7, new ChessPiece};

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

    createDefaultBoard();

    // default current turn to white
    model->changeTurn("white");

    // Create a BoardView that connects with the BoardModel
    BoardView* view = new BoardView{model};

    model->display();

    while (true) {
        currLine = getLine();
        if (currLine == "done") {
            bool canExit = true;

            // check if any pawns are on promotion squares
            if (checkForPawnPromotion(model)) {
                cout << "cannot have pawns in promotion squares" << endl;  // remove later
                canExit = false;
            }

            // Check if there is at least one king on board
            if (!containsTwoKings()) {
                cout << "must have at exactly 1 white king and 1 black king" << endl;
                canExit = false;
            }

            // Check if either king is in check
            if (model->isCheck()) {
                canExit = false;
            } else {
                model->nextTurn();
                if (model->isCheck()) {
                    canExit = false;
                }
                model->nextTurn();  // change back to current turn
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
                    piece = new King{model, pieceName, colour, x, y, new ChessPiece};
                } else if (pieceName == "Q") {
                    piece = new Bishop{model, pieceName, colour, x, y, new ChessPiece};
                } else if (pieceName == "B") {
                    piece = new Bishop{model, pieceName, colour, x, y, new ChessPiece};
                } else if (pieceName == "R") {
                    piece = new Bishop{model, pieceName, colour, x, y, new ChessPiece};

                } else if (pieceName == "N") {
                    piece = new Bishop{model, pieceName, colour, x, y, new ChessPiece};

                } else if (pieceName == "P") {
                    piece = new Bishop{model, pieceName, colour, x, y, new ChessPiece};
                }

                model->addPiece(piece, x, y);

            } else if (command == "-") {
                ss1 >> coord;

                x = parseX(coord);
                y = parseY(coord);

                model->deletePiece(model->getState(x, y));

            } else if (command == "=") {
                ss1 >> colour;

                if (colour == "black") {
                    model->changeTurn("black");
                } else {
                    model->changeTurn("white");
                }
            }
        }
        model->display();
    }
}

void BoardController::runGame() {
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
    string replacePiece;

    // creates a BoardModel called model
    createDefaultBoard();
    
    // default current turn to white
    model->changeTurn("white");

    // Create a BoardView that connects with the BoardModel
    BoardView* view = new BoardView{model};
    
    while (isRunning) {
        string currLine;
        getline(cin, currLine);

        if(cin.eof()){
            break;
        }

        istringstream ss1{currLine};
        ss1 >> command;

        if (command == "move") {
            ss1 >> currCoord;
            ss1 >> nextCoord;

            x1 = parseX(currCoord);
            y1 = parseY(currCoord);

            x2 = parseX(nextCoord);
            y2 = parseY(nextCoord);

            Piece *piece = model->getState(x1, y1);
            if(piece == nullptr){
                cout << "Invalid move. Please enter a valid move. " << endl;
                continue;
            }

            cout << x1 << " " << y1 << " | " << x2 << " " << y2 << endl;
            
            // Promote pawn if its pawn promotion
            if (willPawnPromoteOnMove(piece)) {
                ss1 >> replacePiece;
                try{
                    model->makeMoveWithPawnPromotion(replacePiece, x1, y1, x2, y2);
                }catch (InvalidMoveException &t) {
                    cout << "Invalid move. Please enter a valid move. " << endl;
                    continue;
                }
                model->nextTurn();  // change to next turn
            } else {
                cout << "made it here"<< endl;

                try{
                    // Make normal move or castle
                    model->makeMove(x1, y1, x2, y2);
                }catch (InvalidMoveException &t) {
                    cout << "Invalid move. Please enter a valid move. " << endl;
                    continue;
                }

                model->nextTurn();  // change to next turn
            }

            if (model->isCheck()) {  // if move made mover in check
                cout << model->getTurn() << " "
                     << "is in check." << endl;
            }

            model->nextTurn();
            if (model->isCheck()) {  // if move made opponent in check
                cout << model->getTurn() << " "
                     << "is in check." << endl;
            }
            cout << "ischeck"<< endl;

            model->nextTurn();  // change back to original turn

            if (model->isCheckmate()) {
                cout << "Checkmate! " << model->getTurn() << " wins!" << endl;
                updateScore();
                break;
            }

            if (model->isStalemate()) {
                cout << "Stalemate!" << endl;
                whiteScore += 0.5;
                blackScore += 0.5;
                break;
            }

        } else if (command == "resign") {
            updateScore();
            cout << model->getTurn() << " resigns" << endl;
            break;
        }

        // Display the BoardView(s) that are connected to the BoardModel
        model->display();
    }

    // delete view and model
    delete view;
    delete model;
}

void BoardController::outputWins() {
    // TODO: INSERT CODE
}
