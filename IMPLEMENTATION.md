# CS50 Sudoku Game

## Team Rocket, CS50 Spring 2020

### sudoku

Our *sudoku* game is a standalone program with two functionalities: *create* generates a random sudoku board by removing numbers from a complete grid according to the difficulty specified by the user in the command line; *solve* reads a valid sudoku board from stdin and prints the solved board to stdout.

### Usage

The *sudoku* program is both defined and implemented in `sudoku.c`. The main method validates command-line arguments, expecting either *create* or *solve* as the first command-line argument after `./sudoku`, and calls helper functions accordingly. We have an additional feature of a difficulty rating for our *create* mode, which is toggled by adding an additional command-line argument when calling *create* indicating a difficulty from 1-5.

The *create* functionality implements a difficulty rating from the command line and exports the following functions to support the creator:

```c
/* Takes a difficulty value (1-5) and returns how many numbers to remove from the specific board */
int parseDifficulty(sudoku_t *b, int d);

/* Takes a sudoku board and fills it in completely using the solver functionality */
bool populateBoard(sudoku_t *b);

/* Removes n numbers from a valid sudoku board and checks if board is still unique */
bool removeNumbers(sudoku_t *b, int n);

/* Prints a given board to stdout */
void printBoard(sudoku_t *b, FILE *fp);

/* takes a `sudoku_t` module and frees all associated memory */
bool deleteBoard(sudoku_t *b);
```

The *solve* functionality exports the following functions to support the creator:

```c
/* Loads board from stdin and validates loaded baord for structural validity */
sudoku_t *loadBoard(FILE *fp);

/* Solves a passed board and returns whether or not the solution is unique */
int solveBoard(sudoku_t *b);

/* Prints a given board to stdout */
void printBoard(sudoku_t *b, FILE *fp);

/* takes a `sudoku_t` module and frees all associated memory */
bool deleteBoard(sudoku_t *b);
```

### Implementation

We implement the creator by executing it from the command line with a specified usage syntax, `./sudoku create [difficulty] [maxNumIterations]` where `difficulty` indicates the desired difficulty of the generated sudoku puzzle, between 1-5 where `maxNumIterations` is the maximum number of attempts our `removeBoard` function wil take to generate a board with a unique solution of the desired difficulty

*Create* itself is run by initializing the sudoku grid structure, populating its 3x3 grids along the diagonal, solving the rest of the grid, then removing the number of random cells necessary to generate a sudoku puzzle with a unique solution. 

1. We interpret the desired difficulty of the puzzle to be created
    2. If no difficulty is entered, it is set to a default of 3
    3. If the difficulty entered is above the max (5), it is automatically set to 5
    4. If the difficulty entered is below the min (2), it is automatically set to 1
5. We initialize a structure `sudoku_t` to represent the sudoku grid. The structure contains two parameters: one board, which is a double-pointer array of integers, and the other an integer that specifies the dimensions of the board.
6. The board is initialized with zeros everywhere to represent the empty cells
7. Populate the board
    8. Call `generateRandomGrid` on each of the matrices along the diagonal
        9. For each cell in the 3x3, generate a random number and insert is if it hasn't already been seen by that grid
    10. Use `solveBoard` to recursively fill in the remaining empty cells
11. Call `removeNumbers` to remove the number of cells from the completed grid that satisfies the desired difficulty.
12. While there are still cells to be removed
    13. Choose a random cell number to remove, making sure it is not already empty
    14. Store the value in that cell temporarily and set the cell to empty
    15. If the grid does not have a unique solution, replace the emptied cell with its value
    16. Otherwise, increment the count of cells that have been removed
17. Print the board to stdin for the user
18. Free all memory

*Solve* itself is run by reading in a sudoku puzzle from stdin, then solving the puzzle by filling in empty cells and backtracking when a value cannot be inserted, done recursively until the board is fully populated. The board is then printed for the user. Note that the loaded puzzle need not have a unique solution to be solved.

1. Load in a board
2. Pass the board to the solver.
    3. We first check whether the board has a unique solution
        4. If the board has a unique solution, return 1
        5. Else, return 0 for no solutions or 2 for more than one solution
    6. Go through the puzzle cell by cell and fill in empty ones recursively, checking that there are still empty cells to fill. Each call to `solveBoardHelper` does the following:
        7. Call the solver helper starting from the first cell in the grid, stepping over filled cells until we reach the next empty cell
        8. Starting from a value of 1, insert the value into the empty cell.
        9. If the value is already seen in its row, column, or 3x3 grid, or if a recursive call of `solveBoardHelper` from the next empty cell does not yield a solved board
            10. Increment the value of the number to be inserted and try again
11. If the board is unique with one solution, print the solved puzzle to stdout, else print error and exit
12. Delete the board

### Error Handling and Recovery

The *create* module runs several error checks throughout various functions. We check:

1. In `generateBoard`, whether the `sudoku_t` structure was initialized successfully
2. From the command-line, whether a difficulty setting was entered. If not, set difficulty to default of 3.
3. In `parseDifficulty`, whether the difficulty entered exceeded the bounds of our difficulty setting. If so, normalize the difficulty to the nearest extreme.
4. We attempt to create a board only a [maxNimIterations] amount of times, otherwise we indicate that the board we were trying to populate could not be created successfully.
5. For `removeNumbers`, we attempt to create a puzzle with a unique solution only a certain number of times, particularly relevant for puzzles with a higher difficulty. If failed, we print error and quit.

The *solve* module runs several error checks throughout various functions. We check:

1. Whether a `sudoku_t` structure was properly initalized to store the loaded board
2. Whether a board has no solutions
3. Whether a board has a unique solution

### Persistent Storage

If run successfully, the *create* module will store an unsolved puzzle into a file `test.out`.

### Assumptions

All relevant assumptions can be found in the *README.md* in the common directory.
