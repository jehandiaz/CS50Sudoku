/*
 * helpers.c - implements methods from helpers.h relating to sudoku_t
 * Author: Team Rocket
 * CS50, Spring 2020
 * A board is a 9x9 2D array that holds its size
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "helpers.h"
#include "board.h"
#include "counters.h"

int MIN_SPACES = 17;

/*********** prototypes **************/
static int generateRandomNum(sudoku_t * b, int row, int column);
static int getRandNumber(int min, int max);

static bool solveBoardHelper(sudoku_t *b, int pos);
static bool isNumberPresent(sudoku_t *b, int r, int c, int v);

static bool checkRow(sudoku_t *b, int r, int c, int v);
static bool checkCol(sudoku_t *b, int r, int c, int v);
static bool checkGrid(sudoku_t *b, int r, int c, int v);

static int findArrayRow(sudoku_t *b, int pos);
static int findArrayCol(sudoku_t *b, int pos);

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
void generateRandomGrid(sudoku_t *b, int rStart, int cStart) {
  if (!b || rStart < 0 || cStart < 0 || b->dimension < rStart + 3 || b->dimension < cStart + 3) return;

  // Iterate through each row of the 3x3
  for (int i = rStart; i < rStart + 3; i++) {

    // Iterate through each column of the 3x3
    for (int j = cStart; j < cStart + 3; j++) {

      int insert = generateRandomNum(b, i, j);
      if (!(checkGrid(b, i, j, insert))) {
        b->board[i][j] = insert;
      }
    } 
  }
  return;
}


/********** generateRandomNum **********/
/* 
 * Generates a random number from 1-9 and checks whether that number has already been used 
 * in a given row, column, or grid
 * 
 * Caller provides: 
 *  a set of numbers in a row, column, and grid seen by one cell
 * We guarantee: 
 *  returns a number unique to a row, column, and grid seen by a cell
 * Caller is responsible for: 
 *  Nothing
 */
static int generateRandomNum(sudoku_t * b, int row, int column) {
  int insert;
  while(1) {
    // Generates a random number between 1 and 9
    insert = getRandNumber(1, 9);

    // Check if that number is in the current row, column, and cell
    if (!(checkGrid(b, row, column, insert))) {
      return insert;
    }
  }
  return 0;
}

/************ populateBoard ************/
/*
 * Takes a sudoku board and fills it in completely using the solver functionality
 * 
 * Caller provides:
 *  A valid, empty sudoku board
 * We guarantee:
 *  The board returned is completely filled
 * Caller is responsible for:
 *  Freeing all memory
 */
bool populateBoard(sudoku_t *b) {
  // Populate the diagonal 3x3 grids 
  generateRandomGrid(b, 0, 0);
  generateRandomGrid(b, 3, 3);
  generateRandomGrid(b, 6, 6);

  return solveBoard(b);
}

/************ removeNumbers ************/
/*
 * Removes n numbers from a valid sudoku board and checks if board is still unique
 * 
 * Caller provides:
 *  A valid sudoku board and a number between 0 and n^2 - 17 numbers to remove
 * We guarantee:
 *  A board with one solution is created
 * We return:
 *  True if numbers removed successfully, false if too many iterations or board is non-unique
 * Caller is responsible for:
 *  Nothing
 */
bool removeNumbers(sudoku_t *b, int n) {
  long int maxChecks =  30000;

  if (!b || (((b->dimension) * (b->dimension)) - 17) < n) return false;

  int numRemoved = 0;
  int numIterations = 0;
  while (numRemoved < n) {
    
    // If the loop has iterated too much, return false
    if (numIterations++ >= maxChecks) return false;

    int dim1 = getRandNumber(0, b->dimension - 1);  // generate random number between 0 and 9
    int dim2 = getRandNumber(0, b->dimension - 1);  // do it again

    // Skip any zero spaces
    if (!(b->board[dim1][dim2])) continue;

    int num = b->board[dim1][dim2];             // store number currently in random slot
    b->board[dim1][dim2] = 0;                   // remove number at randomly chosen slot by setting it to 0
    
    if (isUniqueBoard(0, 0, b, 0) == 1)         // check if board created has unique solution
      numRemoved+=1;

    // reset the item changed to original and run through loop again
    else                                      
      b->board[dim1][dim2] = num;
  }

  return true;
}

/************ getRandomNumber ************/
/*
* Generates a random number within the range specified by the parameters and returns to caller
*
* Caller provides:
*   Two ints indicating the minimum and the maximum of the range of numbers in which
*   a random number should be generated
* We guarantee
*   A random int within the specified range is returnned
* Caller is responsible for:
*   Nothing
*/
static int getRandNumber(int min, int max) {
  return (rand() % (max - min + 1) + min);
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
int solveBoard(sudoku_t *b) {
  int numSols = isUniqueBoard(0, 0, b, 0);
  solveBoardHelper(b, 0);
  return numSols;
}

/* 
 * Returns the number of solutions that a sudoku grid has 
 * 
 * Caller provides: 
 *  A valid sudoku grid, a position (0, 0) to start at, the number of solutions
 * We guarantee: 
 *  Returns 0 if no solutions, 1 if board has a unique solution, 2 if board 
 *  has multiple solutions
 *  The passed board is not changed 
 * Caller is responsible for:
 *  Calling deleteBoard
 * 
 * This code takes inspiration from:
 *  https://stackoverflow.com/questions/24343214/determine-whether-a-sudoku-has-a-unique-solution
 */
int isUniqueBoard(int i, int j, sudoku_t* b, int count) {
  if (j == 9) {        // if we have gotten to the end of the first row
        j = 0;
        if (++i == 9)  // if we have gotten to end of the board
            return count+1;
  }

  if (b->board[i][j] != 0)  // skip filled cells
      return isUniqueBoard(i, j + 1, b, count);

  // search for 2 solutions instead of 1
  // return, if 2 solutions are found
  for (int val = 1; val <= 9 && count < 2; ++val) {
      if (!isNumberPresent(b, i, j, val)) {
          b->board[i][j] = val;
          // add additional solutions
          count = isUniqueBoard(i, j + 1, b, count);
      }
  }
  
  b->board[i][j] = 0; // reset on backtrack
  return count;
}


/* 
 * Helper function to solve board, tries plugging in all possible values 
 * and backtracks with recursion until solved
 * 
 * Caller provides:
 *  A unique, unsolved board 
 *  A start position, 0
 * We guarantee: 
 *  Return true if board is solved, false if the board remains unsolved 
 *  Board is solved after function returns 
 * Caller is responsible for:
 *  Freeing all memory
 */
static bool solveBoardHelper(sudoku_t *b, int pos) {

  // Check number of zeros
  int numZeros = 0;
  for (int i = 0; i < b->dimension; i++) {
    for (int j = 0; j < b->dimension; j++) {
      if (!b->board[i][j]) {
        numZeros++;
      }
    }
  }

  // Base case of recursion
  if (!numZeros) return true;

  // Find row and column from position
  int r = findArrayRow(b, pos);
  int c = findArrayCol(b, pos);

  // Step over filled numbers
  if (b->board[r][c]) return solveBoardHelper(b, pos + 1);

  // Number to place
  int currentVal = 1;
  b->board[r][c] = currentVal;

  while (isNumberPresent(b, r, c, currentVal) || !solveBoardHelper(b, pos + 1)) {
    b->board[r][c] = ++currentVal;

    if (currentVal > b->dimension) {
      b->board[r][c] = 0;
      return false;
    }
  }

  return true;
}

/*
 * Checks if a number trying to be inserted is in the current row, column, or 3x3 grid
 * 
 * Caller provides:
 *  A valid sudoku grid, row and column number, value to be inserted
 * We guarantee:
 *  Return true if value is already seen by cell, else return false if value can be inserted
 * Caller is responsible for:
 *  Freeing memory
 */
static bool isNumberPresent(sudoku_t *b, int r, int c, int v) {
  if (checkRow(b, r, c, v)) return true;
  if (checkCol(b, r, c, v)) return true;
  if (checkGrid(b, r, c, v)) return true;

  return false;
}

/*
 * Checks if a number trying to be inserted is in the current row
 * 
 * Caller provides:
 *  A valid sudoku grid, row and column number, and value to be inserted
 * We guarantee:
 *  Return true if value is already seen by cell, else return false if value can be inserted
 * Caller is responsible for:
 *  Freeing memory
 */
static bool checkRow(sudoku_t *b, int r, int c, int v) {
  for (int j = 0; j < b->dimension; j++) {
    if (j == c) continue;
    if (b->board[r][j] == v) return true;
  }

  return false;
}

/*
 * Checks if a number trying to be inserted is in the current column
 * 
 * Caller provides:
 *  A valid sudoku grid, row and column number, and value to be inserted
 * We guarantee:
 *  Return true if value is already seen by cell, else return false if value can be inserted
 * Caller is responsible for:
 *  Freeing memory
 */
static bool checkCol(sudoku_t *b, int r, int c, int v) {
  for (int i = 0; i < b->dimension; i++) {
    if (i == r) continue;
    if (b->board[i][c] == v) return true;
  }

  return false;
}

/*
 * Checks if a number trying to be inserted is in the current 3x3 grid
 * 
 * Caller provides:
 *  A valid sudoku grid, row and column number, and value to be inserted
 * We guarantee:
 *  Return true if value is already seen by cell, else return false if value can be inserted
 * Caller is responsible for:
 *  Freeing memory
 */
static bool checkGrid(sudoku_t *b, int r, int c, int v) {
  int rStart = (int)(r / 3) * 3;      // gets beginning row position of current grid
  int cStart = (int)(c / 3) * 3;      // gets beginning column position of current grid

  for (int i = rStart; i < rStart + 3; i++) {
    for (int j = cStart; j < cStart + 3; j++) {
      if (i == r && j == c) continue;
      if (b->board[i][j] == v) return true;
    }
  }

  return false;
}

/*
 * Returns the row number of a cell in the 9x9 grid
 * 
 * Caller provides:
 *  A valid sudoku board, a position from 0-80
 * We guarantee:
 *  Board is unchanged, returns current row
 * Caller is responsible for:
 *  Freeing memory
 */
static int findArrayRow(sudoku_t *b, int pos) {
  return (int)(pos / b->dimension);
}

/*
 * Returns the column number of a cell in the 9x9 grid
 * 
 * Caller provides:
 *  A valid sudoku board, a position from 0-80
 * We guarantee:
 *  Board is unchanged, returns current column
 * Caller is responsible for:
 *  Freeing memory
 */
static int findArrayCol(sudoku_t *b, int pos) {
  return (int)(pos % b->dimension);
}

/************ parseDifficulty ************/
/*
 * Takes a difficulty value (1-5) and returns how many numbers to remove from the specific board
 * 
 * Caller provides:
 *  A valid difficulty and a valid board
 * We guarantee:
 *  A number of spots to remove from the board that can still return a valid board will be returned
 * Caller is responsible for:
 *  Nothing
 */
int parseDifficulty(sudoku_t *b, int d) {
  const int minDifficulty = 1;
  const int maxDifficulty = 5;

  if (!b) return 0;
  if (d < minDifficulty) d = 1;
  if (d > maxDifficulty) d = 5;

  const int minToRemove = 10;
  const int maxToRemove = (b->dimension * b->dimension) - MIN_SPACES;

  return (d - minDifficulty) * (maxToRemove - minToRemove) / (maxDifficulty - minDifficulty) + minToRemove;
}
