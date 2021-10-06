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
 
 cell.cpp
 ********************************************************************/

#ifndef __Sudoku__Cell__
#define __Sudoku__Cell__

#include <iostream>
#include <vector>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

using namespace std;


class Cell{
private:
    vector<int> numOption;//vector containing 1-9 in random order
    /**/
    int static myrandom (int i);
    
public:
    /*
     constructor that initializes vector with numbers 1-9 
     and then shuffle them into a random order
     */
    Cell();
    
    /*
     gets number from index in numOption vector provided by an int
     */
    int getNum(int);
    
    /*
     returns the size of the numOption Vector
     */
    int getSize();
    

};

#endif /* defined(__Sudoku__Cell__) */
