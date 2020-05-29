/*
 * helpers.h - header file for supporting sudoku board functionality
 * 
 * Author: Team Rocket
 * CS50, Spring 2020
 * 
 * A board is a 9x9 2D array that holds its size
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "board.h"

#ifndef __HELPERS_H
#define __HELPERS_H

// The minimum number of numbers needed to solve a board
const int MIN_SPACES = 17;

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
bool generateRandomGrid(sudoku_t *b, int rStart, int cStart);

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
bool populateBoard(sudoku_t *b);

/************ removeNumbers ************/
/*
 * TODO
 * 
 * Caller provides:
 *  A valid sudoku board
 * We guarantee:
 *  A board with one solution is returned
 * Caller is responsible for:
 *  Nothing
 */
bool removeNumbers(sudoku_t *b, int n);

/************ solveBoard ************/
/*
 * TODO
 * 
 * Caller provides:
 *  A valid sudoku board
 * We guarantee:
 *  A board with one solution is returned
 * Caller is responsible for:
 *  Nothing
 */
bool solveBoard(sudoku_t *b);

#endif // __HELPERS_H