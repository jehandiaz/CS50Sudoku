# CS50 Sudoku Team Project

## Adam McQuilkin, Jehan Diaz, Daniel Akili, Joe Gyorda

## CS50 Spring 2020

## A Sudoku creator and solve made for Dartmouth's CS50 "Introduction to Software Development" class

### sudoku

The *sudoku* program has two functionalities: *create* generates a random sudoku board that for solving, removing numbers according to the difficulty specified by the user in the command line; *solve* reads a valid sudoku board from stdin in prints the solved board to stdout.

### Usage

The *sudoku* program is both defined and implemented in `sudoku.c`. The main method validates command-line arguments, expecting either "create" or "solve" as the first command-line argument after "./sudoku", and calls helper functions accordingly. Note that we added an extra-credit feature so that the *create* mode expects an additional command-line argument indicating a difficulty from 1-5, with 1 removing fewer numbers randomly and 5 removing the most (also note that difficulties of 4 and 5 remove more than the required 40). Helper functions for `sudoku.c` are defined in `board.h` and `helpers.h`, both within the "common" directory of our project. `board.h` defines functions necessary for generating a "sudoku" board stucture, including how to print/delete a board and load from a file. `helpers.h` defines functions necessary for the sudoku board creation and solving. Please see each header file and the "README.md" file in the common directory for further information on these modules.

### Implementation

We implement *sudoku* by with its own C structure: a `sudoku_t` structure has a double array of integers as one parameter and an integer specifying the dimensions of the board (for our program, we assume that it is always 9). For more information on the implementation of each helper module, *board* and *helpers*, please see their respective header files in the "common" directory.

As aforementioned, the `main()` function in *sudoku* first validates its command line arguments, then calls the appropiate helper functions depending on whether the *create* or *solve* mode is indicated in the command line. If *create* is called for, `main` then gets the requested diffuculty from the command line, calling `parseDifficulty()` to determine the number of empty spaces to have in the created sudoku board. `populateBoard()` is then called to create a filled-in sudoku board using the solver functionality. Note that a maximum number of attempts/iterations is defined so that if any issues occur when generating the board the program terminates as opposed to running infinitely. Then, `removeNumbers()` is called to remove the appropiate amount of numbers from the board, guaranteeing the resulting board has a unique solution. Note that a maximum number of attempts to do this is also defined to prevent the program from running infinitely. Finally, `printBoard()` is called twice to print the created board to stdout and to a file "test.out", and `deleteBoard()` is called to free all relevant memory.

If *solve* is called for, `main` then receives a valid sudoku board from stdin (it can be piped in from a file), calling `loadBoard()` to generate a `sudoku_t` structure for the board. `solveBoard()` is then called to fill in the board, indicating the number of solutions discovered by the solver (0 is returned if unsolveable, 1 is returned if solved and the solution is unique, and 2 is returned if the board is solved but 2 or more solutions exist). Depending on the number of solutions, the solved board is either printed to stdout via `printBoard()` (if 1 solution), or an error message is printed (if board not unique or unsolveable). Finally, `deleteBoard()` is called to free all relevant memory.

### Assumptions

All relevant assumptions can be found in the "README.md" in the common directory.

### Exit codes

* **Exit code 0:** successful run
* **Exit code 1:** invalid number of command line arguments
* **Exit code 2:** "create" or "solve" not given as command line argument
* **Exit code 3:** an error occurred when generating/loading a sudoku board
* **Exit code 4:** an error occurred when solving a sudoku board (board could not be solved)

### Compilation

To compile, simply type in the command line `make`.

To test, simply `make test`.
See testing.sh for the code used for a test and testing.out for the output of testing.sh.
See "TESTING.md" for a description of our testing.

Note that `make lib` will compile the "common" directory from the main directory.

### Presentation video link
<https://drive.google.com/file/d/1fhIOPmWFc_cqkLia_pz_tlqTr02iAaYD/view?usp=sharing>
