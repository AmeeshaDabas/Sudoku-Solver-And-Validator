/********************************************************************
 Title:          Sudoku Board Maker
 Author:         Bjorn Johnson
 Created on:     2/15/14.
 Description:    This Program creates a new complete sudoku board
                 when run.
 Purpose:        Demonstrates ability to program using classes as
                 well as implementing recusive functions and
                 backtracking.
 Usage:          User is able to generate as many new boards as they
                 want.
 
 Build with:     g++
 
 sudoku.cpp
 ********************************************************************/

#include <iostream>
#include "Cell.h"
#include "Board.h"
using namespace std;


int main()
{
    char choice = 'a';
    
    while (choice != 'q' && choice != 'Q') {

        cout << "Here is your Sudoku Board" << endl;
        
        Board newBoard;
        newBoard.startTraverse();
        
        cout << "Press 'q' to Quit" << endl
             << "Or any other button to generate another board: " << endl;
        cin >> choice;
        cout << endl << endl;
        
        
    }
    
    
    //Board newBoard;
    //newBoard.startTraverse();
 /*
    Board *boardArray;
    boardArray = new Board;
    
    for (int i = 0; i < 5; i++) {
        boardArray = new Board;
        boardArray->startTraverse();
    }
    
    delete [] boardArray;
  
  */
    return 0;
}

