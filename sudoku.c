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



// exit code 1 = invalid number of arguments
// exit code 2 = invalid command given
int main(int argc, char* argv[]) {
    if (argc < 2) { // Requires at least two valid arguments
        fprintf(stderr, "ERROR: Invalid number of arguments\n");
        return 1;
    }

    char* command = argv[1];
    srand(time(0));

    if (strcmp(command, "create") == 0) {
        printf("Create!\n");
    } else if (strcmp(command, "solve") == 0) {
        printf("Solve!\n");
    } else {
        fprintf(stderr, "ERROR: Command must be either 'create' or 'solve'\n");
        return 2;
    }

    // Test save to file
    sudoku_t *b = generateBoard();
    if (!b) return 3;

    generateRandomGrid(b, 0, 0);
    generateRandomGrid(b, 3, 3);
    generateRandomGrid(b, 6, 6);

    // printBoard(b, stdout);
    // printf("---------\n");

    FILE *fp = fopen("test.out", "w");
    if (!fp) return 4;

    // for (int r = 0; r < b->dimension; r++) {
    //     for (int c = 0; c < b->dimension; c++) {
    //         b->board[r][c] = (rand()%9) + 1;
    //     }
    // }
    printBoard(b, fp);

    // removeNumbers(b, argv[2] ? atoi(argv[2]) : 15);
    printf("Generated board\n");
    printBoard(b, stdout);
    printf("---------\n");

    deleteBoard(b);
    fclose(fp);

    // Test read from file
    FILE *fr = fopen("test.out", "r");
    if (!fr) return 5;

    b = loadBoard(fr);
    if (!b) return 6;
    fclose(fr);

    printf("THIS SHOULD BE SOLVED PLZ\n");
    
    if (testSolver(b)) printf("Solved!!\n");
    else printf("Stop that\n");

    printf("Solved board\n");
    printBoard(b, stdout);
    printf("---------\n");

    removeNumbers(b, argv[2] ? atoi(argv[2]) : 15);
    printf("Numbers removed\n");
    printBoard(b, stdout);
    printf("---------\n");

    if (testSolver(b)) printf("Solved!!\n");
    else printf("Stop that\n");

    printf("Re-solved board\n");
    printBoard(b, stdout);
    deleteBoard(b);

    return 0;
}
