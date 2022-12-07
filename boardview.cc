// boardview.cc
#include "boardview.h"
#include "window.h"
#include "piece.h"
#include <string>
#include <iostream>
using namespace std;

BoardView::BoardView(BoardModel *subject) :  subject{subject} {
    
    // Text version is 10 wide x 11 height characters,
    // so graphic version will be 100 x 110

    int cols = 10;
    int rows = 11;
    win = new Xwindow{100 * rows, 100 * cols};
    subject->attach(this);
}

void BoardView::notify(){
    // Cout board as text
    textDisplay();

    // Display to board to user in graphic form
    graphicDisplay();
}

int BoardView::pieceLetterToColour(std::string piece){
    char p = piece[0];

    // convert to lower
    if('A' <= p && p <= 'Z'){
        p = p - 'A' + 'a';
    }

    if(p == 'p'){
        return 1;
    }
    else if(p == 'r'){
        return 2;
    }
    else if(p == 'q'){
        return 3;
    }
    else if(p == 'b'){
        return 4;
    }
    else if(p == 'k'){
        return 7;
    }
    else if(p == 'n'){
        return 8;
    }
    else{
        return 0;
    }
}

void BoardView::textDisplay(){
    // Goal:
    /*
        8 rnbqkbnr
        7 pppppppp
        6  _ _ _ _ 
        5 _ _ _ _ 
        4  _ _ _ _ 
        3 _ _ _ _ 
        2 PPPPPPPP
        1 RNBQKBNR

        abcdefgh
    */

    // Cout current board as text
    for(int i = 7; i >= 0; i--){
        int row = i + 1;
        // Output row number before each horizontal line on the board
        cout << row << " ";

        for(int j = 0; j < 8; j++){
            int col = j + 1;
            if(subject->getState(j, i) == nullptr){
                // all even rows have a white square on odd columns
                if(row % 2 == 0){
                    if(col % 2 == 0){
                        cout << "_";
                    }
                    else{
                        cout << " ";
                    }
                }
                // all odd rows have a black square on odd columns
                else{
                    if(col % 2 == 0){
                        cout << " ";
                    }
                    else{
                        cout << "_";
                    }
                }
            }
            // Otherwise output the piece if the chess square is not empty
            else{
                string name = subject->getState(j, i)->getName();

                // cout the name as lowercase, if the colour is black
                if(subject->getState(j, i)->getColour() == "black"){
                    char letter = name[0];
                    char lowercase = (letter - 'A' + 'a');
                    cout << lowercase;
                }
                else{
                    cout << name;
                }
            }
        }
        cout << endl;
    }

    // Output the bottom line at the end
    cout << "\n  abcdefgh" << endl;
}

void BoardView::graphicDisplay(){
    // Goal:
    /*
        8 rnbqkbnr
        7 pppppppp
        6  _ _ _ _ 
        5 _ _ _ _ 
        4  _ _ _ _ 
        3 _ _ _ _ 
        2 PPPPPPPP
        1 RNBQKBNR

        abcdefgh
    */

    // Cout current board as text
    for(int i = 7; i >= 0; i--){
        int row = i + 1;
        string rowToText = row + "";
        // Output row number before each horizontal line on the board
        // Old: cout << row << " ";
        // win->fillRectangle(0, i * 10, pieceLetterToColour(rowToText));

        for(int j = 0; j < 8; j++){
            int col = j + 1;
            if(subject->getState(j, i) == nullptr){
                win->fillRectangle(j * 100, 700 - i * 100, 100, 100, 0);
                // all even rows have a white square on odd columns
                if(row % 2 == 0){
                    if(col % 2 == 0){
                        // Recall old text version: cout << "_" << endl;
                        //win->drawString(j * 10, i * 10, "_");
                    }
                    else{
                        // Recall old text version: cout << " " << endl;
                        //win->drawString(j * 10, i * 10, " ");
                    }
                }
                // all odd rows have a black square on odd columns
                else{
                    if(col % 2 == 0){
                        // Recall old text version: cout << " " << endl;
                        //win->drawString(j * 10, i * 10, " ");
                    }
                    else{
                        // Recall old text version: cout << "_" << endl;
                        //win->drawString(j * 10, i * 10, "_");
                    }
                }
            }
            // Otherwise output the piece if the chess square is not empty
            else{
                string name = subject->getState(j, i)->getName();

                // cout the name as lowercase, if the colour is black
                if(subject->getState(j, i)->getColour() == "black"){
                    char letter = name[0];
                    char lowercase = (letter - 'A' + 'a');
                    string lower = string(1, lowercase);
                    // Recall old text version: cout << lowercase;;
                    // win->drawString(j * 10, i * 10, lower);
                    win->fillRectangle(j * 100, 700 - i * 100, 100, 100, 0);
                    win->fillRectangle(10 + j * 100, 10 + 700 - i * 100, 80, 80, pieceLetterToColour(lower));
                }
                else{
                    // Recall old text version: cout << name;
                    //win->drawString(j * 10, i * 10, name);
                    win->fillRectangle(j * 100, 700 - i * 100, 100, 100, pieceLetterToColour(name));
                }
            }
        }
    } 
}

BoardView::~BoardView(){
    subject->detach(this);
}


