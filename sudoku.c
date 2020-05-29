/*
* Joe Gyorda, Adam McQuilkin, Daniel Akili, Jehan Diaz
* May 2020
* CS 50 Team Project (Sudoku) - Team Rocket (woop!)
* sudoku.c
*/

// #include <cs1lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "helpers.h"


// exit code 1 = invalid number of arguments
// exit code 2 = invalid command given
int main(int argc, char* argv[]) {
    if (argc < 2) { // Requires at least two valid arguments
        fprintf(stderr, "ERROR: Invalid number of arguments\n");
        return 1;
    }

    char* command = argv[1];

    if (strcmp(command, "create") == 0) {
        printf("Create!\n");
    } else if (strcmp(command, "solve") == 0) {
        printf("Solve!\n");
    } else {
        fprintf(stderr, "ERROR: Command must be either 'create' or 'solve'\n");
        return 2;
    }

    sudoku_t *b = generateBoard();
    printBoard(b);
    deleteBoard(b);

    return 0;
}




// create
// display output in a file?


// solver
// keep track of number of times each number appears in each row, 
// column, and 3x3 square with counters


