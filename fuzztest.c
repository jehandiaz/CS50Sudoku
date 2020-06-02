/* 
 * fuzzSudoku.c - generate a series of random sudoku puzzles for testing solver
 * 
 * usage: 
 *      fuzzSudoku numPuzzles 
 * 
 * Team Rocket - May/June 2020
 * CS50 Spring 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "board.h"
#include "helpers.h"
#include "counters.h"

bool isBoardChanged(sudoku_t *b, sudoku_t *solved); 

int main (int argc, char *argv[])
{
    // parse the arguments
    // function exits if any errors parsing the arguments
    if (argc < 2) {                 // Requires at least 2 valid arguments 
        fprintf(stderr, "ERROR: invalid number of arguments\n");
        return 1;
    }

    srand(time(0));

    int numPuzzles = atoi(argv[1]);  // get number of random puzzles to generate from command-line
    int testsPassed = 0;

    int created = 0;                 // puzzles created so far 
    sudoku_t *b, *unsolved;
    while (created < numPuzzles) {
        created++;
        b = generateBoard();         // generate the board structure
        if (!b) return 2;
        populateBoard(b);            // populate the board until it is full

        int difficulty = (rand() % (4 - 1 + 1) + 1);   // set the difficulty level
        int numToRemove = parseDifficulty(b, difficulty);
        
        if (!(removeNumbers(b, numToRemove))) break;   // break test if too many iterations or a non-unique puzzle
        unsolved = b;
        int numSols = solveBoard(b);
        if (numSols != 1) break;                       // break if non-unique solution
        if (isBoardChanged(b, unsolved)) break;        // break if already filled cells are changed by solver

        deleteBoard(b);
        testsPassed++;
    }
    printf("Passed %d/%d tests!\n", testsPassed, numPuzzles);
    return 0;
}

/* 
 * Checks whether sudoku solver changes already fill cells in the grid
 * 
 * Caller provides:
 *  valid sudoku puzzle with unique solution
 *  valid solved sudoku puzzle
 * We guarantee: 
 *  Returns true if already filled cells in grid remained unaltered after calling solver
 * Caller is responsible for:
 *  Freeing memory
 */
bool isBoardChanged(sudoku_t *b, sudoku_t *solved) {
    for (int i = 0; i < b->dimension; i++) {
        for (int j = 0; j < b->dimension; j++) {
            int cell = b->board[i][j];
            if ((cell != 0) && (cell != solved->board[i][j])) return true;
        }
    }
    return false;
}