//
//  main.cpp
//  Sudoku Solver And Validator
//
//  Created by Ameesha Dabas on 03/11/20.
//

#include<iostream>
#include<fstream>
using namespace std;

class SudokuFrame{
    
    int sudokuFrame[9][9];
    int editableFrame[9][9];
    public:SudokuFrame(){
        display_menu();
    }
    
   
    private:void display_menu(){
        
        cout<<"\n==============================\n";
        cout<<"  Sudoku Solver And validator\n";
        cout<<"==============================\n\n";

        cout<<"Welcome to the Sudoku Solver And Validator!\n";
        cout<<"Before we start, you will have to input the puzzle into this program.\n\n";
        cout<<"You can :-\n";
        cout<<"\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
        
        cout<<"\t   Blank cells must be filled in as 0 (For example; 3 0 1 0 0 0 ...).\n";
        cout<<"\t   --> ";

        int option;
        cin>>option;

        if(option==1) readFrameValues();
        else{
            while(true){
                cout<<"\nOops!! You have entered an invalid option. Try again.\n";
                cout<<"\t   --> ";
                cin>>option;

                if(option==1) readFrameValues();
                else continue;

                break;
            }
        }

    }

   
    private:void readFrameValues(){
        cout<<"\nEnter the specified values.\n";
        cout<<"Enter 0 if cell is empty.\n\n";
        
        int row_val, col_val;

        for(row_val=0; row_val<9; row_val++){
            for(col_val=0; col_val<9; col_val++){
                int value;

                cout<<"Enter the value for cell["<<row_val+1<<"]["<<col_val+1<<"] --> ";
                cin>>value;

                if(!(value>=0 && value<=9)){
                    while(true){
                        cout<<"Oops! You have entered a wrong value! Try again.\n";
                        cout<<"Enter the value for cell ["<<row_val+1<<"]["<<col_val+1<<"] --> ";
                        cin>>value;

                        if(value>=0 && value<=9) break;
                    }
                }

                sudokuFrame[row_val][col_val]=value;

                if(value==0) editableFrame[row_val][col_val]=0;
                else editableFrame[row_val][col_val]=1;
            }
            cout<<"-------\n";
        }
    }
    
   
    public:void setCellValue(int row, int col, int num){
        if(editableFrame[row][col]==0) sudokuFrame[row][col]=num;
    }
    
    
    public:int getCellVal(int row, int col){
        int cellValue=sudokuFrame[row][col];
        return cellValue;
    }
    
   
    public:int isEditable(int row, int col){
        return (editableFrame[row][col]-1)*(-1);
    }

   
    public:void clearFrameFrom(int row, int col){
        int jcount=0;
        int row_val, col_val;

        for(row_val=row; row_val<9; row_val++){
            
            if(jcount==0) col_val=col;
            else col_val=0;

            for(; col_val<9; col_val++){
                if(editableFrame[row_val][col_val]==0) sudokuFrame[row_val][col_val]=0;
            }

            jcount++;

        }
    }

    public:void displayFrame(){

        cout<<"==========================================";
        int row_val, col_val;

        for(row_val=0; row_val<9; row_val++){
            int cellIter=1;

            cout<<"\n";
            for(col_val=0; col_val<9; col_val++){
                if(cellIter==3){
                    cout<<sudokuFrame[row_val][col_val]<<"   ||   ";
                    cellIter=1;
                }
                else{
                    cout<<sudokuFrame[row_val][col_val]<<"  ";
                    cellIter++;
                }
            }

            if(row_val%3!=2) cout<<"\n";
            else cout<<"\n==========================================";
        }

    }
    
};

class Possibilities{
    
    struct node{
        int value;
        struct node* next;
    };
    typedef struct node* Node;

    Node head;
    Node pos;
    
    public:Possibilities(){
        head=new struct node;
        head->next=NULL;
    }
    
    public:~Possibilities(){
        destroy();
    }
    public:void append(int number){
        Node temp=new struct node;

        temp->value=number;
        temp->next=NULL;

        pos=head;
        while(pos!=NULL){
            if(pos->next==NULL){
                pos->next=temp;
                break;
            }
            pos=pos->next;
        }
    }
        public:int operator[](int index){
        int count=0;
        pos=head->next;
        
        while(pos!=NULL){
            if(count==index)
                return pos->value;
            pos=pos->next;
            count++;
        }

        return -1;
    }

    public:void print(){
        pos=head->next;
        while(pos!=NULL){
            cout<<pos->value<<",";
            pos=pos->next;
        }
        cout<<"\b";
    }

    public:int length(){
        pos=head->next;
        int count=0;

        while(pos!=NULL){
            count++;
            pos=pos->next;
        }
        
        return count;
    }
        public:void copy(Possibilities possibilities){
        int oldLength=possibilities.length();
        int iter=0;
        
        pos=head;
        for(iter=0; iter<oldLength; iter++){
            Node temp=new struct node;

            temp->next=NULL;
            temp->value=possibilities[iter];

            pos->next=temp;
            pos=pos->next;
        }
    }
    
    private:void destroy(){
        Node temp;
        pos=head;
        while(pos!=NULL){
            temp=pos;
            pos=pos->next;
            delete temp;
        }
    }

};


class SudokuSolver{
    
    int recursiveCount;
    SudokuFrame frame;
    
    public:SudokuSolver(){
        recursiveCount=0;
        
        solve();
        cout<<" Yay! Your puzzle has been solved!\n\n";
        displayFrame();

        cout<<"\n\n";
    }
    
    private:bool cellValueValid(int row, int col, int currentValue){
        int row_val, col_val;

        for(row_val=0; row_val<9; row_val++){
            if(row_val!=row){
                int comparingVal=frame.getCellVal(row_val,col);
                if(comparingVal==currentValue) return false;
            }
        }

        for(col_val=0; col_val<9; col_val++){
            if(col_val!=col){
                int comparingVal=frame.getCellVal(row,col_val);
                if(comparingVal==currentValue) return false;
            }
        }
        if(ThreeByThreeGridValid(row,col,currentValue)==false) return false;

        return true;
    }
    
    private:bool ThreeByThreeGridValid(int row, int col, int currentValue){
        int rowStart=(row/3)*3;
        int rowEnd=(rowStart+2);

        int colStart=(col/3)*3;
        int colEnd=(colStart+2);

        int row_val, col_val;

        for(row_val=rowStart; row_val<=rowEnd; row_val++){
            for(col_val=colStart; col_val<=colEnd; col_val++){
                if(frame.getCellVal(row_val,col_val)==currentValue) return false;
            }
        }

        return true;
    }
    
    private:Possibilities getCellPossibilities(int row, int col){
        int iter=0;

        Possibilities possibilities;

        for(iter=1; iter<=9; iter++){
            if(cellValueValid(row,col,iter)==true)
                possibilities.append(iter);
        }

        return possibilities;
    }
    
    private:int singleCellSolve(int row, int col){
        
        statsIncrement();

        if(frame.isEditable(row,col)==true){

            Possibilities possibilities;
            possibilities.copy(getCellPossibilities(row,col));

            int posLength=possibilities.length();
            int posIter=0, newRow=row, newCol=col;

            for(posIter=0; posIter<posLength; posIter++){
                int possibility=possibilities[posIter];
                frame.setCellValue(row,col,possibility);
                
                if(col<8) newCol=col+1;
                else if(col==8){
                    if(row==8) return 1;
                    newRow=row+1;
                    newCol=0;
                }

                {

                    if(singleCellSolve(newRow,newCol)==0){
                        frame.clearFrameFrom(newRow,newCol);
                    }
                    else return 1;

                }

            }

            return 0;
            
        }
        else{

            int newRow=row, newCol=col;
        
            if(col<8) newCol=col+1;
            else if(col==8){
                if(row==8) return 1;
                newRow=row+1;
                newCol=0;
            }

            return singleCellSolve(newRow,newCol);

        }

    }

  
    private:void solve(){
        int success=singleCellSolve(0,0);
    }
    
   
    private:void displayFrame(){
        frame.displayFrame();
    }
    
    private:void statsIncrement(){
        recursiveCount++;
    }

   
    public:void statsPrint(){
        cout<<"\nThe singleCellSolve() function was recursively called "<<recursiveCount<<" times.\n";
    }
    class SudokuValidator{

        SudokuFrame frame;
        
        public:SudokuValidator(){
            validateFrame();
        }

        private:void validateFrame(){
            if(values_Valid()){
                if(rows_Valid()){
                    if(columns_Valid()){
                        if(Three_By_Three_Squares_Valid()){
                            cout<<"\nYour puzzle is valid!\n\n";
                        }
                        else cout<<"Your puzzle in invalid!\n";
                    }
                    else cout<<"Your puzzle is invalid!\n";
                }
                else cout<<"Your puzzle is invalid!\n";
            }
            else cout<<"Your puzzle is invalid!\n";
        }
        

        private:bool values_Valid(){
            int row_val, col_val;

            for(row_val=0; row_val<9; row_val++){
                for(col_val=0; col_val<9; col_val++){
                    int cellValue=frame.getCellVal(row_val,col_val);
                    if(!(cellValue>=0 && cellValue<=9)) return false;
                }
            }

            return true;
        }
        private:bool rows_Valid(){
            
            int row_val, col_val, val;

            for(row_val=0; row_val<9; row_val++){

                for(val=1; val<=9; val++){

                    if(rowContains(row_val,val)==false)
                        return false;

                }
            }
            return true;
        }

       
        private:bool columns_Valid(){
            
            int row_val, col_val, val;
            
            for(col_val=0; col_val<9; col_val++){
            
                for(val=1; val<=9; val++){
                    
                    if(columnContains(col_val,val)==false)
                        return false;

                }
            }
            
            return true;
        }
        
       
        private:bool Three_By_Three_Squares_Valid(){
            
            int squareIter, valIter;

            for(squareIter=0; squareIter<9; squareIter++){
                
                for(valIter=1; valIter<=9; valIter++){

                    if(squareContains(squareIter,valIter)==false)
                        return false;

                }

            }
            
            return true;
        }

       
        private:bool rowContains(int row, int value){
            int colIter;
            for(colIter=0; colIter<9; colIter++){
                if(frame.getCellVal(row,colIter)==value)
                    return true;
            }
            return false;
        }

        private:bool columnContains(int col, int value){
            int rowIter=0;
            for(rowIter=0; rowIter<9; rowIter++){
                if(frame.getCellVal(rowIter,col)==value)
                    return true;
            }
            return false;
        }

        
        private:bool squareContains(int squareNum, int val){
            int rowStart=(squareNum/3)*3;
            int rowEnd=rowStart+2;
            
            int colStart=(squareNum%3)*3;
            int colEnd=colStart+2;

            int row_val, col_val;
            for(row_val=rowStart; row_val<=rowEnd; row_val++){
                for(col_val=colStart; col_val<=colEnd; col_val++){
                    if(frame.getCellVal(row_val,col_val)==val)
                        return true;
                }
            }

            return false;
        }

    };

    
};

int main(){
    int choice;
    cout<<"Please Enter your choice\n ";
    cout<<"You can :-\n";
    cout<<"\t1.To Solve a Sudoku. (Enter 1)\n";
    
    cout<<"\t2.To Check the validity of an existing sudoku.(Enter 2)\n";
    cout<<"\t   --> ";
    cin>>choice;
    if(choice==1)
    {
    SudokuSolver s;
    }
    if(choice==2)
    {
        SudokuSolver::SudokuValidator s;
    }
    if(choice!=1 && choice!=2)
    {
            while(1){
                cout<<"\nOops!! You have entered an invalid choice. Please Try again.\n";
                cout<<"\t   --> ";
                cin>>choice;

                if(choice==1) SudokuSolver s;
                else if (choice==2) SudokuSolver::SudokuValidator s;
                else continue;
                break;
            }
        
    }
    return 0;
}
