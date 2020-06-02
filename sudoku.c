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
        if (!b) return 2;


        // Get required parameters for creating board
        int difficulty = argv[2] ? atoi(argv[2]) : DEFAULT_DIFFICULTY;
        int numToRemove = parseDifficulty(b, argv[2] ? atoi(argv[2]) : 3);
        // int numToRemove = atoi(argv[2]);
        int maxNumIterations = argv[3] ? atoi(argv[3]) : MAX_ITERATIONS;

        printf("Selected difficulty [%i], removing [%i] numbers from board with [%i] maximum tries...\n", difficulty, numToRemove, maxNumIterations);

        // Hold until a valid solution can be created by creating a board
        int populateTries = 0;
        while (!populateBoard(b) && populateTries < maxNumIterations) { printf("Re-attempting populateBoard (%i)\n", populateTries++); }
        
        // If no valid solution was created, creating failed
        if (populateTries == maxNumIterations) {
            fprintf(stderr, "Could not solve board, exiting...\n");
            deleteBoard(b);
            return 3;
        }
        
        // Hold until a valid board can be created by removing numbers
        int removeTries = 0;
        printf("num to be removed: %d\n", numToRemove);
        while (!removeNumbers(b, numToRemove) && removeTries < maxNumIterations) { printf("Re-attempting removeNumbers (%i)\n", removeTries++); }

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
        printf("Solve!\n");

        // TODO: Read from other files from cmdline
        FILE *loadFile = stdin;

        b = loadBoard(loadFile);
        if (!b) return 2;

        int solveResult = solveBoard(b);

        if (!solveResult) {
            fprintf(stderr, "Could not find any solutions to loaded board\n");
        } else if (solveResult == 1) {
            printf("Solved board!\n");
            printBoard(b, stdout);
        } else {
            fprintf(stderr, "Board not unique\n");
        }

        deleteBoard(b);
    } else {
        fprintf(stderr, "ERROR: Command must be either 'create' or 'solve'\n");
        return 2;
    }

    // // Test save to file
    // sudoku_t *b = generateBoard();
    // if (!b) return 3;

    // generateRandomGrid(b, 0, 0);
    // generateRandomGrid(b, 3, 3);
    // generateRandomGrid(b, 6, 6);

    // // printBoard(b, stdout);
    // // printf("---------\n");

    // FILE *fp = fopen("test.out", "w");
    // if (!fp) return 4;

    // // for (int r = 0; r < b->dimension; r++) {
    // //     for (int c = 0; c < b->dimension; c++) {
    // //         b->board[r][c] = (rand()%9) + 1;
    // //     }
    // // }
    // printBoard(b, fp);

    // // removeNumbers(b, argv[2] ? atoi(argv[2]) : 15);
    // printf("Generated board\n");
    // printBoard(b, stdout);
    // printf("---------\n");

    // deleteBoard(b);
    // fclose(fp);

    // // Test read from file
    // FILE *fr = fopen("test.out", "r");
    // if (!fr) return 5;

    // b = loadBoard(fr);
    // if (!b) return 6;
    // fclose(fr);

    // printf("THIS SHOULD BE SOLVED PLZ\n");
    
    // if (solveBoard(b)) printf("Solved!!\n");
    // else printf("Stop that\n");

    // printf("Solved board\n");
    // printBoard(b, stdout);
    // printf("---------\n");

    // removeNumbers(b, argv[2] ? atoi(argv[2]) : 15);
    // printf("Numbers removed\n");
    // printBoard(b, stdout);
    // printf("---------\n");

    // if (solveBoard(b)) printf("Solved!!\n");
    // else printf("Stop that\n");

    // printf("Re-solved board\n");
    // printBoard(b, stdout);
    // deleteBoard(b);

    return 0;
}
