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
#include <time.h>

#include "board.h"

#ifndef __HELPERS_H
#define __HELPERS_H

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
void generateRandomGrid(sudoku_t *b, int rStart, int cStart);

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

/************ solveBoard ************/
/*
 * Takes a board and returns the number of solutions the board has as well as updating the board to the first solution
 * 
 * Caller provides:
 *  A valid sudoku board
 * We guarantee:
 *  A board with one solution is returned
 * Caller is responsible for:
 *  Nothing
 */
bool solveBoard(sudoku_t *b);

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
int parseDifficulty(sudoku_t *b, int d);

#endif // __HELPERS_H