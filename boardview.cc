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
    win = new Xwindow{10 * rows, 10 * cols};
    subject->attach(this);
}

void BoardView::notify(){
    // Cout board as text
    textDisplay();

    // Display to board to user in graphic form
    graphicDisplay();
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
    // Goal (in graphic version):
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

   for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            int col = j + 1;
            int row = i + 1;

            string rowToText = row + "";

            // Output row number before each horizontal line on the board
            // Recall old text version: cout << row << " ";
            win->drawString(j * 10, i * 10, rowToText);
            
            if(subject->getState(j, i) == nullptr){
                // all even rows have a white square on odd columns
                if(row % 2 == 0){
                    if(col % 2 == 0){
                        // Recall old text version: cout << "_" << endl;
                        win->drawString(j * 10, i * 10, "_");
                    }
                    else{
                        // Recall old text version: cout << " " << endl;
                        win->drawString(j * 10, i * 10, " ");
                    }
                }
                // all odd rows have a black square on odd columns
                else{
                    if(col % 2 == 0){
                        // Recall old text version: cout << " " << endl;
                        win->drawString(j * 10, i * 10, " ");
                    }
                    else{
                        // Recall old text version: cout << "_" << endl;
                        win->drawString(j * 10, i * 10, "_");
                    }
                }
            }
            // Otherwise output the piece if the chess square is not empty
            else{
                string name = subject->getState(j, i)->getName();

                // cout the name as lowercase, if the colour is black
                if(subject->getState(j, i)->getColour() == "black"){
                    char letter = name[0];
                    name = (letter - 'A' + 'a') + "";
                }
                // Recall old text version: cout << name;
                win->drawString(j * 10, i * 10, name);
            }
        }
        // Recall old text version: cout << endl;
    }

    // Output the bottom line at the end
    // Recall old text version: cout << "\n  abcdefgh" << endl;
    win->drawString(20, 100, "abcdefgh");    
}

BoardView::~BoardView(){
    subject->detach(this);
}


