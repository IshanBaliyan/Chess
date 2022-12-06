#include "computer.h"

#include <cstdlib>
#include <map>
#include <string>
#include <utility>

#include "boardmodel.h"
#include "invalidmoveexception.h"

using namespace std;

// Constructor
Computer::Computer(string type, string colour, Piece* boardIn[8][8]) : type{type}, colour{colour} {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = boardIn[i][j];

            // Add each piece to the set of black pieces or set of white pieces for future use
            if (board[i][j]->getColour() == "black") {
                blackPieces.push_back(board[i][j]);
            } else {
                whitePieces.push_back(board[i][j]);
            }
        }
    }
}

Piece* Computer::getRandPiece() {
    int randNum;

    if (colour == "white") {
        randNum = rand() % whitePieces.size();  // random number from 0 to number of white pieces
        return whitePieces[randNum];
    } else {
        randNum = rand() * blackPieces.size();
        return blackPieces[randNum];
    }
}

void Computer::addToMoveList(int x, int y) {
    pair<int, int> coords;
    coords.first = x;
    coords.second = x;
    movesList.push_back(coords);
}

bool Computer::checkMove(int currX, int currY, int nextX, int nextY) {
    bool canMove = false;
    BoardModel* boardmodel = new BoardModel(board);
    try {
        boardmodel->makeMove(currX, currY, nextX, nextY);
        canMove = true;
        boardmodel->undo();
    } catch (InvalidMoveException& t) {
        canMove = false;
    }

    return canMove;
}

void Computer::findPossibleMoves(Piece* piece) {
    int currX = piece->getX();
    int currY = piece->getY();
    int nextX = currX;
    int nextY = nextY;
    pair<int, int> coords;

    int maxX = 7;
    int maxY = 7;
    int minX = 0;
    int minY = 0;

    if (piece->getName() == "P") {
        if (piece->getColour() == "white") {  // add possible moves if piece is white pawn
            nextY++;
            if (checkMove(currX, currY, nextX, nextY)) {  // check if can move forward one square
                addToMoveList(nextX, nextY);
            }

            nextY = currY + 2;
            if (checkMove(currX, currY, nextX, nextY)) {  // check if pawn can move two spaces forward
                addToMoveList(nextX, nextY);
            }

            nextX = currX + 1;
            nextY = currY + 1;
            if (checkMove(currX, currY, nextX, nextY)) {  // check if pawn can capture to right
                addToMoveList(nextX, nextY);
            }

            nextX = currX - 1;
            nextY = currX + 1;
            if (checkMove(currX, currY, nextX, nextY)) {  // check if pawn can capture to left
                addToMoveList(nextX, nextY);
            }
        } else {  // add possible moves if piece is black pawn
            nextY--;
            if (checkMove(currX, currY, nextX, nextY)) {  // check if can move forward one square
                addToMoveList(nextX, nextY);
            }

            nextY = currY - 2;
            if (checkMove(currX, currY, nextX, nextY)) {  // check if pawn can move two spaces forward
                addToMoveList(nextX, nextY);
            }

            nextX = currX + 1;
            nextY = currY - 1;
            if (checkMove(currX, currY, nextX, nextY)) {  // check if pawn can capture to right
                addToMoveList(nextX, nextY);
            }

            nextX = currX - 1;
            nextY = currX - 1;
            if (checkMove(currX, currY, nextX, nextY)) {  // check if pawn can capture to left
                addToMoveList(nextX, nextY);
            }
        }
    }

    if (piece->getName() == "N") {
        nextX++;
        nextY += 2;
        if (checkMove(currX, currY, nextX, nextY)) {
            addToMoveList(nextX, nextY);
        }

        nextY = currY - 2;
        if (checkMove(currX, currY, nextX, nextY)) {
            addToMoveList(nextX, nextY);
        }

        nextX = currX - 1;
        nextY = currY + 2;
        if (checkMove(currX, currY, nextX, nextY)) {
            addToMoveList(nextX, nextY);
        }

        nextY = currY - 2;
        if (checkMove(currX, currY, nextX, nextY)) {
            addToMoveList(nextX, nextY);
        }
    }

    if ((piece->getName() == "R") || (piece->getName() == "Q")) {  // add possible moves for rook
        while (nextX <= maxX) {                                    // possible moves to the right
            nextX++;
            if (checkMove(currX, currY, nextX, nextY)) {
                addToMoveList(nextX, nextY);
            }
        }

        nextX = currX;
        while (nextX >= minX) {  // possible moves to left
            nextX--;
            if (checkMove(currX, currY, nextX, nextY)) {
                addToMoveList(nextX, nextY);
            }
        }

        while (nextY >= maxY) {
            nextY++;
            if (checkMove(currX, currY, nextX, nextY)) {
                addToMoveList(nextX, nextY);
            }
        }

        nextY = currY;
        while (nextY <= minY) {
            nextY--;
            if (checkMove(currX, currY, nextX, nextY)) {
                addToMoveList(nextX, nextY);
            }
        }
    }

    if ((piece->getName() == "B") || (piece->getName() == "Q")) {
        while ((nextX <= maxX) && (nextY <= maxY)) {
            nextX++;
            nextY++;
            if (checkMove(currX, currY, nextX, nextY)) {
                addToMoveList(nextX, nextY);
            }
        }

        nextX = currX;
        nextY = currY;
        while ((nextX <= maxX) && (nextY >= minY)) {
            nextX++;
            nextY--;
            if (checkMove(currX, currY, nextX, nextY)) {
                addToMoveList(nextX, nextY);
            }
        }

        nextX = currX;
        nextY = currY;
        while ((nextX >= minX) && (nextY <= maxY)) {
            nextX--;
            nextY++;
            if (checkMove(currX, currY, nextX, nextY)) {
                addToMoveList(nextX, nextY);
            }
        }

        nextX = currX;
        nextY = currY;
        while ((nextX >= minX) && (nextY >= minY)) {
            nextX--;
            nextY--;
            if (checkMove(currX, currY, nextX, nextY)) {
                addToMoveList(nextX, nextY);
            }
        }
    }

    if (piece->getName() == "K") {
        if (checkMove(currX, currY, nextX + 1, nextY + 1)) {
            addToMoveList(nextX + 1, nextY + 1);
        }

        if (checkMove(currX, currY, nextX + 1, nextY - 1)) {
            addToMoveList(nextX + 1, nextY - 1);
        }

        if (checkMove(currX, currY, nextX - 1, nextY + 1)) {
            addToMoveList(nextX - 1, nextY + 1);
        }

        if (checkMove(currX, currY, nextX - 1, nextY - 1)) {
            addToMoveList(nextX - 1, nextY - 1);
        }
    }
}

string Computer::convertMove(int x, int y) {
    map<int, string> xMap;
    map<int, string> yMap;

    xMap[0] = "a";
    xMap[1] = "b";
    xMap[2] = "c";
    xMap[3] = "d";
    xMap[4] = "e";
    xMap[5] = "f";
    xMap[6] = "g";
    xMap[7] = "h";

    yMap[0] = "1";
    yMap[1] = "2";
    yMap[2] = "3";
    yMap[3] = "4";
    yMap[4] = "5";
    yMap[5] = "6";
    yMap[6] = "7";
    yMap[7] = "8";

    return xMap[x] + yMap[y];
}

string Computer::getRandomMove() {
    int randNum;
    pair<int, int> randCoords;
    int x;
    int y;

    Piece* piece = getRandPiece();

    findPossibleMoves(piece);
    randNum = rand() % movesList.size();
    randCoords = movesList[randNum];
    x = randCoords.first;
    y = randCoords.second;

    return convertMove(x, y);
}

int Computer::getLevel() {
    level = name[9];
    return level;
}

// Public methods:

// Computer returns strategic move
string Computer::getMove() {
    // TODO: [Insert Code for finding strategic move]
    // 4 levels of computer

    // LEVEL 1:
    if (level == 1) {
        return getRandomMove();
    }
}

string Computer::getType() const {
    return type;
}

string Computer::getColour() const {
    return colour;
}
