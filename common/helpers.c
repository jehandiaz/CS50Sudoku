/*
 * helpers.c - implements methods from helpers.h relating to sudoku_t
 * Author: Team Rocket
 * CS50, Spring 2020
 * A board is a 9x9 2D array that holds its size
 */

#include "helpers.h"
#include "board.h"

/************ generateRandomGrid ************/
/*
 * Populates a specified 3x3 grid within the board with numbers 1-9
 * 
 * Caller provides:
 *  A valid sudoku board
 * We guarantee:
 *  Each number is used only once
 * Caller is responsible for:
 *  Nothing
 */
bool generateRandomGrid(sudoku_t *b, int rStart, int cStart) {
  //if (!b || rStart < 0 || cStart < 0 || b->dimension <= rStart + 3 || b->dimension <= cStart + 3) return false;

  return false;
}

/************ populateBoard ************/
/*
 * Takes a sudoku board and fills it in completely using the solver functionality
 * 
 * Caller provides:
 *  A valid sudoku board
 * We guarantee:
 *  A board with one solution is returned
 * Caller is responsible for:
 *  Nothing
 */
bool populateBoard(sudoku_t *b) {
  if (!b) return false;

  return false;
}

/************ removeNumbers ************/
/*
 * Removes n numbers from a valid sudoku board and checks if board is still unique
 * 
 * Caller provides:
 *  A valid sudoku board and a number between 0 and n^2 - 17 numbers to remove
 * We guarantee:
 *  A board with one solution is returned
 * Caller is responsible for:
 *  Nothing
 */
bool removeNumbers(sudoku_t *b, int n) {
  //if (!b || (b->dimension) * (b->dimension) - MIN_SPACES < n) return false;


  return false;
}

/************ solveBoard ************/
/*
 * Solves a passed board and returns whether or not the solution is unique
 * 
 * Caller provides:
 *  A valid sudoku board
 * We guarantee:
 *  The passed board is solved with one solution or false is returned
 * Caller is responsible for:
 *  Nothing
 */
bool solveBoard(sudoku_t *b) { 

    int **board = b->board;         // get the board
    int dimension = b->dimension;   // get the dimension

    // count the number of cells to fill
    int cellsToFill = 0;

    for (int i=0; i<dimension; i++){
      for (int j=0; j<dimension; j++){

        // if there is a cell value with value 0, increment cellsToFill
        if (board[i][j] == 0){
          cellsToFill++;
        }

      }
    }


    // if the number if cellsToFill is 0; then the puzzle is solved, return true.
    if (cellsToFill == 0){
      return true;
    }

    int newValue;         // value to fill empty cells (should be between 1 and 9)
    int row;            // keeps track of rows
    int col;            // keeps track of columns

    // check for every possible new value entry
    for (newValue = 1; newValue<= dimension; newValue++){

      // iterate over the current row and check if the value already exists
      for (int i=0; i<dimension; i++){
        if (board[row][i] == newValue){
            continue;       // do nothing if the value already exists
        }
      }

      // iterate over the current column and check if the value already exists
      for (int j=0; j<dimension; j++){
        if (board[j][col] == newValue){
          continue;       // do nothing
        }
      }

      // iterate over the 3x3 squared region and check if the value already exists
      int squareRow = (row/3)*3;
      int squareCol = (col/3)*3;
      for (int i = squareRow; i<squareRow+3; i++){
        for (int j = squareCol; j<squareCol+3; j++){
          if (board[i][j] == newValue){
              continue;    // do nothing is the value already exists
          }
        }
      }

      // else fill the cell with the new value
      board[row][col] = newValue;
      
      // if the solving was done correctly, return true
      if (solveBoard(b)){
        return true;
      }

      // else, change that value to 0
      board[row][col] = 0;

    }

    return false;


  /*
  if (!b) return false;

  return false; */
}
