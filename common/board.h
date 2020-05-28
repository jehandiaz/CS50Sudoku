/*
 * board.h - header file for integrated sudoku board functionality
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

#ifndef __BOARD_H
#define __BOARD_H

typedef struct sudoku sudoku_t;

/************ generateBoard ************/
/*
 * Generates a blank 9x9 sudoku board filled with 0s
 * 
 * Caller provides:
 *  Nothing
 * We guarantee:
 *  Board is initialized empty
 * Caller is responsible for:
 *  Calling deleteBoard on the returned sudoku_t
 */
sudoku_t *generateBoard();

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


/************ printBoard ************/
/*
 * Prints a given board to stdout
 * 
 * Caller provides:
 *  A valid pointer to a sudoku_t structure
 * We guarantee:
 *  Nothing
 * Caller is responsible for:
 *  Calling deleteBoard on the returned sudoku_t
 */
void printBoard(sudoku_t *b);

/************ loadBoard ************/

/*
 * Loads board from stdin and validates loaded baord for structural validity
 * 
 * Caller provides:
 *  Valid file pointer to read from
 * We guarantee:
 *  Returned board is valid or NULL
 * Caller is responsible for:
 *  Calling deleteBoard on the returned sudoku_t
 */
sudoku_t *loadBoard(FILE *fp);

/************ deleteBoard ***********/
/*
 * takes a `sudoku_t` module and frees all associated memory
 * 
 * Caller provides:
 *  A valid pointer to a sudoku_t structure
 * We guarantee:
 *  All relevant memory is freed
 * Caller is responsible for:
 *  Nothing
 */
bool deleteBoard(sudoku_t *b);

#endif // __BOARD_H