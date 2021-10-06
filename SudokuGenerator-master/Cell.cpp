//
//  Cell.cpp
//  Sudoku
//
//  Created by bjorn on 2/15/14.
//  Copyright (c) 2014 Bjorn. All rights reserved.
//

#include "Cell.h"
Cell::Cell(){
    srand (unsigned(time(NULL)));
    for(int i = 0; i < 9; i++){
        numOption.push_back(i+1);
    }
    random_shuffle ( numOption.begin(), numOption.end(), myrandom);
    
}
int Cell::myrandom (int i) {
    return rand()%i;}

int Cell::getNum(int num){
    num = numOption[num];
    return num;
}

int Cell::getSize(){

    return numOption.size();
}