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

counters_t *getRow(sudoku_t *b, int r);
counters_t *getColumn(sudoku_t *b, int col);
int generateRandomNum(counters_t *row, counters_t *column, counters_t *cell);

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
  //srand(time(0));
  counters_t *grid = counters_new();

  // Iterate through each row of the 3x3
  for (int i = rStart; i < rStart + 3; i++) {
    counters_t *row = getRow(b, rStart);

    // Iterate through each column of the 3x3
    for (int j = cStart; j < cStart + 3; j++) {
      counters_t *column = getColumn(b, cStart);
      int insert = generateRandomNum(row, column, grid);
      counters_add(grid, insert);
      b->board[i][j] = insert;
      counters_delete(column);
      } 
      
    counters_delete(row);
  }

  counters_delete(grid);
  return;
}

counters_t *getRow(sudoku_t *b, int r) {
  counters_t *row = counters_new();
  for (int i = 0; i < b->dimension; i++) {
    if (!(b->board[r][i] == 0)) {
      counters_add(row, b->board[r][i]);
    }
  }
  return row;
}

counters_t *getColumn(sudoku_t *b, int col) {
  counters_t *column = counters_new();
  for (int i = 0; i < b->dimension; i++) {
    if (!(b->board[i][col] == 0)) {
      counters_add(column, b->board[i][col]);
    }
  }
  return column;
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
int generateRandomNum(counters_t *row, counters_t *column, counters_t *grid) {
  int insert;
  while(1) {
    // Generates a random number between 1 and 9
    insert = (rand()%9) + 1;

    // Check if that number is in the current row, column, and cell
    if (counters_get(row, insert) == 0 && counters_get(column, insert) == 0 && counters_get(grid, insert) == 0) {
      return insert;
    }
  }
  return insert;
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
  if (!b || (b->dimension) * (b->dimension) - MIN_SPACES < n) return false;

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
  if (!b) return false;

  return false;
}
