#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const int DIMENSION = 20;

void initialize(/*in*/bool life[][DIMENSION], /*in*/bool life2[][DIMENSION]);      //Function prototype
void readFile(/*in*/bool life[][DIMENSION], /*in*/bool life2[][DIMENSION]);        //Function prototype
void printBoard(/*in*/bool life[][DIMENSION]);                                     //Function prototype
int liveCells(/*in*/bool life[][DIMENSION], /*in*/int, /*in*/int);                 //Function prototype
int deadCells(/*in*/bool life[][DIMENSION], /*in*/int, /*in*/int);                 //Function prototype
void nextGen(/*in*/bool life[][DIMENSION], /*in*/bool life2[][DIMENSION]);         //Function prototype
void nextBoard(/*in*/bool life[][DIMENSION], /*in*/bool life2[][DIMENSION]);       //Function prototype



int main()
{
    bool life[DIMENSION][DIMENSION];            //2D array with 20 rows and 20 columns
    bool life2[DIMENSION][DIMENSION];           //2D array with 20 rows and 20 columns
    int row,
        col;

    readFile(life, life2);                      //Read from the file bacteria.txt
    printBoard(life);                           //Output the first board

    for(int count = 0; count < 5; count++){     //Count up to 5 generations
        nextGen(life, life2);
        nextBoard(life, life2);
    }

    return 0;
}



/****************************************************************
 *                      initialize                              *
 * This function initializes the bools life and life2 to false  *
 * in each row and column of the arrays.                        *
 ****************************************************************/
void initialize(bool life[][DIMENSION], bool life2[][DIMENSION])
{
    for(int row = 0; row < DIMENSION; row++){               //Initialize every cell to false
        for(int col = 0; col < DIMENSION; col++){
            life[row][col] = false;
        }
    }
    for(int row = 0; row < DIMENSION; row++){               //Initialize every cell to false
        for(int col = 0; col < DIMENSION; col++){
            life2[row][col] = false;
        }
    }
}
//bools life and life1 have been initialized to false




/************************************************************************
 *                          readFile                                    *
 * This function reads from the file bacteria.txt to fill the arrays.   *
 ************************************************************************/
void readFile(bool life[][DIMENSION], bool life2[][DIMENSION])
{
    ifstream textfile;
    int row,
        col;                       //Loop counters

    textfile.open("bacteria.txt");
    initialize(life, life2);
    textfile >> row >> col;
    while(textfile){
        life[row][col] = true;
        textfile >> row >> col;
    }
}
//Data from file bacteria.txt has been stored




/************************************************************************
 *                          printBoard                                  *
 * This function outputs the gameboard. It also calculates and displays *
 * the number of living and dead bacteria in row and column 10 of the   *
 * current game board iteration, as well as the number of living and    *
 * dead bacteria on the game in total.                                  *
 ************************************************************************/
void printBoard(bool life[][DIMENSION])
{
    int rTotal,         //Row totals
        cTotal,         //Column totals
        sum = 0;        //Board totals, initialized to 0

    cout << "  01234567890123456789" << endl;
    for(int row = 0; row < DIMENSION; row++){
        cout << setw(2) << row;
        for(int col = 0; col < DIMENSION; col++){
            if(life[row][col]){
                cout << "*";
            }
            else{
                cout << " ";
            }
        }
        cout << endl;
    }
    for(int row = 0; row < DIMENSION; row++){               //Sum row 10
        rTotal = 0;
        for(int col = 0; col < DIMENSION; col++){
            rTotal += life[10][col];
        }

    }
    for(int col = 0; col < DIMENSION; col++){               //Sum column 10
        cTotal = 0;
        for(int row = 0; row < DIMENSION; row++){
            cTotal += life[row][9];
        }
    }
    for(int row = 0; row < DIMENSION; row++){               //Sum entire board
        for(int col = 0; col < DIMENSION; col++){
            sum += life[row][col];
        }
    }
      cout << "Total alive in row 10 = " << rTotal << endl;
      cout << "Total dead in row 10 = " << (20 - rTotal) << endl;
      cout << "Total alive in column 10 = " << cTotal << endl;
      cout << "Total dead in column 10 = " << (20 - cTotal) << endl;
      cout << "Total alive = " << sum << endl;
      cout << "Total dead = " << (400 - sum) << endl << endl;
}
//Game board and totals have been ouput





 /*******************************************************************
  *                            liveCells                            *
  * This function counts and returns the number of live neighbors   *
  * for each cell in the board.                                     *
  *******************************************************************/
 int liveCells(bool life[DIMENSION][DIMENSION], int row, int col)
 {
    int lifeCount=0;

    if(life[row][col]== true && life[row][col-1]==true && col-1 >= 0){                       //Check Left
        lifeCount++;
    }
    if(life[row][col]== true && life[row+1][col-1]==true && row+1 < 20 && col-1 >= 0){       //Check Bottom Left
        lifeCount++;
    }
    if(life[row][col]== true && life[row+1][col]==true && row+1 < 20){                       //Check Bottom
        lifeCount++;
    }
    if(life[row][col]== true && life[row][col+1]==true && col+1 < 20){                       //Check Right
        lifeCount++;
    }
    if(life[row][col]== true && life[row-1][col-1]==true && row-1 >= 0 && col-1 >= 0 ){      //Check Top Left
        lifeCount++;
    }
    if(life[row][col]== true && life[row+1][col+1]==true && row+1 < 21 && col+1<20){        //Check Bottom Right
        lifeCount++;
    }
    if(life[row][col]== true && life[row-1][col]==true && row-1>=0){                        //Check Top
        lifeCount++;
    }
    if(life[row][col]== true && life[row-1][col+1]==true && row-1>=0 && col+1<20){          //Check Top Right
        lifeCount++;
    }

    return lifeCount;
 }
 //Live cell neighbors have been counted




/****************************************************************
 *                      deadCells                               *
 * This function counts and return the number of dead neighbors *
 * for each cell in the game.                                   *
 ****************************************************************/
int deadCells(bool life[DIMENSION][DIMENSION], int row, int col)
{
    int deadCount = 0;

    if(life[row][col]== false && life[row][col-1]==true && col-1 >= 0){                     //Check Left
        deadCount++;
    }
    if(life[row][col]== false && life[row+1][col-1]==true && row+1 < 20 && col-1 >= 0){     //Check Bottom Left
        deadCount++;
    }
    if(life[row][col]== false && life[row+1][col]==true && row+1 < 20){                     //Check Bottom
        deadCount++;
    }
    if(life[row][col]== false && life[row][col+1]==true && col+1 < 20){                     //Check Right
        deadCount++;
    }
    if(life[row][col]== false && life[row-1][col-1]==true && row-1 >= 0 && col-1 >= 0 ){    //Check Top Left
        deadCount++;
    }
    if(life[row][col]== false && life[row+1][col+1]==true && row+1 < 20 && col+1 < 20){     //Check Bottom Right
        deadCount++;
    }
    if(life[row][col]== false && life[row-1][col]==true && row-1 >= 0){                     //Check Top
        deadCount++;
    }
    if(life[row][col]== false && life[row-1][col+1]==true && row-1>=0 && col+1 < 20){       //Check Top Right
        deadCount++;
    }

    return deadCount;
}
//Dead cell neighbors have been counted




/***********************************************************
 *                  nextGen                                *
 * This function uses the rules of the game to determine   *
 * which cells will be alive and dead in the next iteration*
 * of the board.                                           *
 ***********************************************************/
void nextGen(bool life[][DIMENSION], bool life2[][DIMENSION])
{
    int lifeCount = 0,
        deadCount = 0;

    for(int row = 0; row < DIMENSION; row++){
        for(int col = 0; col < DIMENSION; col++){
            lifeCount = liveCells(life, row, col);
            if(lifeCount <= 1){                         //If a living cell has 1 or 0 living neighbors
                life2[row][col] = false;
            }
            else if(lifeCount >= 4){                    //If a living cell has 4 or more living neighbors
                life2[row][col] = false;
            }
            else if(lifeCount == 2 || lifeCount == 3){  //If a living cell has 2 or 3 living neighbors
                life2[row][col] = true;
            }
        }
        for(int row = 0; row < DIMENSION; row++){
            for(int col = 0; col < DIMENSION; col++){
                deadCount = deadCells(life, row, col);
                if(deadCount == 3){                       //If a dead cell has 3 dead neighbors
                    life2[row][col] = true;
                }
            }
        }
    }
}
//The next board iteration has been calculated



/****************************************************************
 *                      nextBoard                               *
 * This function sets each cell in the array "life" equal to    *
 * the values calculated in the function nextGen, so that the   *
 * board will output correctly.                                 *
 ****************************************************************/
void nextBoard(bool life[][DIMENSION], bool life2[][DIMENSION])
{
    printBoard(life2);
    for(int row = 0; row < DIMENSION; row++){
        for(int col = 0; col < DIMENSION; col++){
            life[row][col] = life2[row][col];               //Swap the arrays.
        }
    }
}
//Arrays have been swapped

5 Attachments
 
 
