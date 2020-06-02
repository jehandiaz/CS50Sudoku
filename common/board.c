/*
 * board.c - implements methods from board.h relating to sudoku_t
 * Author: Team Rocket
 * CS50, Spring 2020
 * A board is a 9x9 2D array that holds its size
 */

#include "board.h"
#include <stdlib.h>
#include <stdbool.h>


typedef struct sudoku {
  int **board;   // Points to a 2D array of values holding the board
  int dimension; // Tells parsers how long each row and column are
} sudoku_t;


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
sudoku_t *generateBoard() {
  const int boardSize = 9;

  sudoku_t *newBoard = malloc(sizeof(sudoku_t));
  if (!newBoard) return NULL;

  int** newBoardArray = calloc(boardSize, sizeof(int *));
  if (!newBoardArray) return NULL;

  for (int i = 0; i < boardSize; i++) {
    int* temp = calloc(boardSize, sizeof(int));
    if (!temp) return NULL;
    newBoardArray[i] = temp;
  }

  newBoard->board = newBoardArray;
  newBoard->dimension = boardSize;
  
  return newBoard;
}



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
void printBoard(sudoku_t *b, FILE *fp) {
  if (!b || !fp) return;

  for (int i = 0; i < b->dimension; i++) {
    for (int j = 0; j < b->dimension; j++) {
      fprintf(fp, "%i ", b->board[i][j]);
    }

    fprintf(fp, "\n");
  }
}

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
sudoku_t *loadBoard(FILE *fp) {
  if (!fp) return NULL;

  sudoku_t *loadedBoard = generateBoard();
  if (!loadedBoard) return NULL;
  
  // Iterate through each row (carrage-return friendly)
  int rCount = 0;
  while (rCount < loadedBoard->dimension) {

    // Iterate through each column (space-friendly)
    int cCount = 0;
    while (cCount < loadedBoard->dimension) {

      // Get each character from fp, check if char is a digit, and insert if so
      char ch = fgetc(fp);
      if (ch == '\n') { rCount++; break; };
      if (!isdigit(ch)) { continue; }

      // Convert char to int value (ASCII)
      loadedBoard->board[rCount][cCount] = (int)ch - 48;
      cCount++;
    }
  }

  return loadedBoard;
}

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
bool deleteBoard(sudoku_t *b) {
  if (!b) return false;

  for (int i = 0; i < b->dimension; i++) {
    free(b->board[i]);
  }
  
  free(b->board);
  free(b);
  b = NULL;
  
  return true;
}
