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
 
 board.cpp
 ********************************************************************/

#ifndef __Sudoku__Board__
#define __Sudoku__Board__

#include <iostream>
#include <vector>
#include <string>
#include "Cell.h"
using namespace std;

class Board{
private:
    int boardArray[81];
    int counter;
    
    
    /*
     recursive function to check if chosen input already exists
     in row, column, and square.  Also Backtracks if invalid
     conclusion is reached
     */
    bool traverse(int counter);
    
    /*
     checks row for duplicate number
     */
    bool getRow(int num, int choice);
    
    /*
     checks column for duplicate number
     */
    bool getColumn(int num, int choice);
    
    /*
     additional function to figure out the begining cell of
     a square
     */
    int cellRange(int num);
    
    /*
     checks square for duplicate number
     */
    bool getSquare(int num, int choice);
    
    /*
     formats and prints finished array to look like sudoku board
     */
    void printBoard();
public:
    /*
     constructor to initialize array and counter to 0
     */
    Board();
    
    /*
     public function to call traverse and print functions
     */
    void startTraverse();


};



#endif /* defined(__Sudoku__Board__) */
