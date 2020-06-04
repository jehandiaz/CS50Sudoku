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
#include <time.h>

#include "board.h"
#include "helpers.h"
#include "counters.h"

const int MAX_ITERATIONS = 30;
const int DEFAULT_DIFFICULTY = 3;

// exit code 1 = invalid number of arguments
// exit code 2 = invalid command given
int main(int argc, char* argv[]) {
    if (argc < 2) { // Requires at least two valid arguments
        fprintf(stderr, "ERROR: Invalid number of arguments\n");
        return 1;
    }

    char* command = argv[1];
    srand(time(0));

    sudoku_t *b = NULL;
    if (strcmp(command, "create") == 0) {
        b = generateBoard();
        if (!b) return 3;


        // Get required parameters for creating board
        int difficulty = argv[2] ? atoi(argv[2]) : DEFAULT_DIFFICULTY;
        int numToRemove = parseDifficulty(b, difficulty);
        // int numToRemove = atoi(argv[2]);
        int maxNumIterations = argv[3] ? atoi(argv[3]) : MAX_ITERATIONS;

        // printf("Selected difficulty [%i], removing [%i] numbers from board with [%i] maximum tries...\n", difficulty, numToRemove, maxNumIterations);

        // Hold until a valid solution can be created by creating a board
        int populateTries = 0;
        while (!populateBoard(b) && populateTries < maxNumIterations) { fprintf(stderr, "Re-attempting populateBoard (%i)\n", populateTries++); }
        
        // If no valid solution was created, creating failed
        if (populateTries == maxNumIterations) {
            fprintf(stderr, "Could not solve board, exiting...\n");
            deleteBoard(b);
            return 4;
        }
        
        // Hold until a valid board can be created by removing numbers
        int removeTries = 0;
        // printf("num to be removed: %d\n", numToRemove);
        while (!removeNumbers(b, numToRemove) && removeTries < maxNumIterations) { fprintf(stderr, "Re-attempting removeNumbers (%i)\n", removeTries++); }

        // If no valid solution was created, creating failed
        if (removeTries == maxNumIterations) {
            fprintf(stderr, "Could not solve board, exiting...\n");
            deleteBoard(b);
            return 4;
        }

        FILE *fp;
        fp = fopen("test.out", "w");
        printBoard(b, fp);
        fclose(fp);

        printBoard(b, stdout);
        deleteBoard(b);
    
    } else if (strcmp(command, "solve") == 0) {
        // printf("Solve!\n");

        // TODO: Read from other files from cmdline
        FILE *loadFile = stdin;

        b = loadBoard(loadFile);
        if (!b) return 3;

        int solveResult = solveBoard(b);

        if (!solveResult) {
            fprintf(stderr, "Could not find any solutions to loaded board\n");
        } else if (solveResult == 1) {
            #ifdef TESTING
                printf("Board has a unique solution.\n");
            #endif
            printBoard(b, stdout);
        } else {
            #ifdef TESTING
                printf("Board does not have a unique solution.\n");
            #endif
            printBoard(b, stdout);

        }

        deleteBoard(b);
    } else {
        fprintf(stderr, "ERROR: Command must be either 'create' or 'solve'\n");
        return 2;
    }

    return 0;
}
