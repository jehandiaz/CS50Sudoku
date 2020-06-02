# CS50 Sudoku Team Project
## Adam McQuilkin, Jehan Diaz, Daniel Akili, Joe Gyorda
## CS50 Spring 2020
## A Sudoku creator and solve made for Dartmouth's CS50 "Introduction to Software Development" class


### common.a
The *common.a* archive is built via the corresponding object files of three separate modules: *board* and *helpers*. The functionalities defined in these helper modules that are used by the main `sudoku.c` program: 

The *board* module defines functions necessary to perform operations on a `sudoku_t` structure, which stores a double array of integers representing the sudoku board, along with and integer representing the dimensions of the board (we assume for this lab that it will always be 9). The module includes functions for allocating memory for a new structure/deleting a structure from memory, loading a structure from a file, and printing a structure to a file.

The *helpers* module defines functions necessary for creating and solving a sudoku board. It implements some of the functionalities defined in the *board* module, mainly the `sudoku_t` structure. The module includes functions for randomly generating a completely-filled and valid sudoku board, removing numbers from a filled board so that the resulting board has a unique solution, and taking this board and solving it by filling in the blank spaces (note that the solver will also solve sudoku boards with more than one solution). Note that for extra credit we added a function to this module that sets the "difficulty" of the sudoku board made by *create* by removing an amount of numbers according to the indicated difficulty.


### Usage

The *board* module is defined in `board.h` and implemented in `board.c`.

```c
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
void printBoard(sudoku_t *b, FILE *fp);

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

```

The *helpers* module is defined in `helpers.h` and implemented in `helpers.c`.

```c
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

/************ removeNumbers ************/
/*
 * Removes n numbers from a valid sudoku board and checks if board is still unique
 * 
 * Caller provides:
 *  A valid sudoku board and a number between 0 and n^2 - 17 numbers to remove
 * We guarantee:
 *  A board with one solution is created
 * We return:
 *  True if numbers removed successfully, false if too many iterations or board is non-unique
 * Caller is responsible for:
 *  Freeing all memory
 */
bool removeNumbers(sudoku_t *b, int n);

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
int solveBoard(sudoku_t *b);

/**************** isUniqueBoard **************/
/* 
 * Returns the number of solutions that a sudoku grid has 
 * 
 * Caller provides: 
 *  A valid sudoku grid, a position (0, 0) to start at, the number of solutions
 * We guarantee: 
 *  Returns 0 if no solutions, 1 if board has a unique solution, 2 if board 
 *  has multiple solutions
 *  The passed board is not changed 
 * Caller is responsible for:
 *  Calling deleteBoard
 * 
 * This code takes inspiration from:
 *  https://stackoverflow.com/questions/24343214/determine-whether-a-sudoku-has-a-unique-solution
 */
int isUniqueBoard(int i, int j, sudoku_t* b, int count);

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

```


### Implementation

See the "README.md" file for the main directory as well as the "IMPLEMENTATION.md" file for more information on how the functionalities of the helper modules are implemented in `solver.c`.


### Assumptions

We assume (loosly) in both modules that the dimension of the `sudoku_t` structure being used has dimension of 9 (the code can be easily revised to make it more generally, but it was more convenient to make this assumption for removing numbers and setting a difficulty).

We assume in the *helpers* module that all aspects of the solver functionality give starting solve position of i=0, j=0, and count (number of solutions) = 0.

We assume in the *board* module that `loadBoard()` always receives a pointer to a file produced by *create* or that follows the format of a 9x9 sudoku grid as outlined in the requirements of this project.


### Compilation

To compile, simply type in the command line `make` within the "common" directory or `make lib` within the main directory.
