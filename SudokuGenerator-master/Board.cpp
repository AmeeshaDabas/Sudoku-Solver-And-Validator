//
//  Board.cpp
//  Sudoku
//
//  Created by bjorn on 2/15/14.
//  Copyright (c) 2014 Bjorn. All rights reserved.
//

#include "Board.h"
Board::Board(){
    for (int i = 0; i< 80; i++) {
        boardArray[i] = 0;
    }
    
    counter = 0;
}


bool Board::traverse(int counter){
    bool done = true;
    int choice = 0;

    Cell newCell;
    
    choice = newCell.getNum(0);
    
    /*
     if last cell of array and meets all criteria
     returns done
     */
    if (counter == 80) {
        for (int i = 0; i < newCell.getSize(); i++) {
            
            choice = newCell.getNum(i);
            
            if (getRow(counter, choice) == false
                && getColumn(counter, choice) == false
                && getSquare(counter, choice) == false) {
                
                    boardArray[counter] = choice;
                
                    return done;
                
            }
        }
    }
    
    /*
     sets first cell of board to random number
     from cell array and calls travers with updated
     counter
     */
    if (counter == 0) {
        boardArray[counter] = choice;
        counter++;
        traverse(counter);
    }
    
    
    /*
     this loops through randomized cell array
     calling traverse with a new values and
     returning done if a valid input is found
     */
    for (int i = 0; i < newCell.getSize(); i++) {
        choice = newCell.getNum(i);
        if (getRow(counter, choice) == false
            && getColumn(counter, choice) == false
            && getSquare(counter, choice) == false) {
            
                boardArray[counter] = choice;
                counter++;
                if (traverse(counter) == true) {
            
                return done;
            }
        }
    }
    
    done = false;
    return done;
}


bool Board::getRow(int num, int choice){
    bool foundMatch = false;
    int mod = num%9;
    
    
    for (int i = 0; i < num; i ++) {
        if (mod == (i%9)) {
            
            if (boardArray[i] == choice) {
                foundMatch = true;
                
            }
        }
    }
    
        return foundMatch;
    
}


bool Board::getColumn(int num, int choice){
    
    bool foundMatch = false;
    int quotient = num/9;
    
    for (int i = 0; i < num; i ++) {
        
        if (quotient == i/9) {
            if (boardArray[i] == choice) {
                
                foundMatch = true;
                
            }
        }
    }
    return foundMatch;
}

int Board::cellRange(int num){
    if (num < 3) {
        return 0;
    }
    if (num < 6) {
        return 3;
    }
    if (num < 9) {
        return 6;
    }
    
    return 0;
}

bool Board::getSquare(int num, int choice){
    bool foundMatch = false;
    int mod = num%9;
    int quotient = num/9;
    
    /*
     this for loop figures out numbers in the 
     square using mod and quotient to find the 
     range then checks for matching number in cell
     */
    for (int i = 0; i < num; i++) {
        
        if  (( i/9 == cellRange(quotient)
            || i/9 == (cellRange(quotient) +1)
            || i/9 == (cellRange(quotient) +2))
            &&(i%9 == (cellRange(mod))
            || i%9 == (cellRange(mod) +1)
            || i%9 == (cellRange(mod) +2))) {
                
                if (boardArray[i] == choice) {
                    
                    foundMatch = true;
                    
            }
        }
    }
    
    return foundMatch;
}


void Board::startTraverse(){
    traverse(0);
    printBoard();
}


void Board::printBoard(){
    for (int i = 0; i < 81; i++) {
        if (i%27 == 0) {
            cout << endl << "---------------------";
        }
        if (i%9 == 0) {
            cout << endl << boardArray[i] << " ";
        }
        else if (i%3 == 0) {
            cout << "| " << boardArray[i] << " ";
        }
        else{
            cout << boardArray[i] << " ";
        }
    }
    cout << endl << "---------------------";
    cout << endl << endl;
}