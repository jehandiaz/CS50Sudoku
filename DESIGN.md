# Team Rocket Sudoku Design Spec

## Dartmouth CS50, May-June 2020

Sudoku is well known logic puzzle where numbers between 1 and 9 are placed on a 9x9 grid of cells. The placement of numbers has to follow certain rules. There are many variations of Sudoku, but for this project you will be looking at only the most common version of Sudoku. In this version the 9x9 grid is further divided into 9 square shaped regions of size 3x3 as shown below.

### User interface

The Sudoku's only interface with the user is on the command-line; it must always have one argument.

```bash
sudoku action
```

For example:

```bash
./sudoku create
./sudoku solve
```

Additional elements of UI may be added as the project progresses per the needs of the end user.

### Inputs and outputs

Input: the only inputs are command-line parameters; see the User Interface above.

Output: If "create" is given as command-line argument, a 9x9 sudoku puzzle with empty spaces is displayed in stdout. If "solve" is given as command-line argument, the sudoku puzzle just outputted by "create" is solved then outputted to stdout. The sudoku puzzle is represented as 9 lines in the following format, where zeroes imply empty slots:

```text
[R0] 1 2 3 4 5 6 7 8 9
[R1] 1 0 2 3 0 9 1 2 4
...
[R8] 0 9 3 4 5 7 0 0 0
```

### Functional decomposition into modules

We anticipate the following modules or functions:

* **main** which parses arguments and initializes other modules

* **generateBoard** which initializes and returns an empty `sudoku_t` data structure
* **populateBoard** which takes an empty board and returns a filled board
* **generateRandomGrid** which randomly fills a specified 3x3 area within a passed board
* **removeNumbers** which takes a complete board, removes values, and makes sure solution is still unique for each removed value
* **deleteBoard** which takes a `sudoku_t` module and frees all associated memory

* **solve** which takes a passed sudoku board and solves it, assuming the board has only one solution, else return error
* **printBoard** which prints a given board to stdout
* **loadBoard** which reads from `stdin` and loads the board into a valid board structure

And some helper modules that provide data structures:

* **set** which we will use to validate that a board has a unique solution and that it follows the rules of sudoku
* **sudoku_t** which is a modified version of a 2D array that holds both its size and its values (see below)

### Pseudo code for logic/algorithmic flow

The `sudoku` module will run with the command line arguments shown above. **Note:** if `solve` is selected a valid string representation of a `sudoku_t` must be piped in to `stdin`.

Pseudocode for the operation of the module is shown below in **Dataflow through modules** section.

### Dataflow through modules

* **main** which parses arguments and checks whether to run *create* or *solve* functionality

#### Create

* **generateBoard** initializes an empty `sudoku_t` structure and passes it to **populateBoard**
* **generateRandomGrid** takes a pointer to the `sudoku_t` board and fills the 3x3 grid specified by **populateBoard**
* **populateBoard** which takes an empty board and runs **generateRandomGrid** on the diagonal 3x3 squares within the board
* **removeNumbers** which takes complete puzzle from **populateBoard**, removes 40+ values, and makes sure there is still only one solution using **solveBoard**
* **printBoard** prints the created board to `stdout`
* **deleteBoard** which takes the board and frees all associated memory

#### Solve

* **loadBoard** which reads the passed board (if a valid board is passed) from `stdin` and loads the board into a valid `sudoku_t` structure
* **solveBoard** which takes a passed `sudoku_t` from **loadBoard** and solves it, assuming the board has only one solution, and returns an error if not
* **printBoard** prints the solved board to `stdout`
* **deleteBoard** which takes the board and frees all associated memory

### Major data structures

Helper modules that provide data structures:

* **set** which we will use to validate that a board has a unique solution and that it follows the rules of sudoku
* **sudoku_t** which is a modified version of a 2D array that holds both its size and its values (see below)

```c
typedef struct sudoku {
  int **board;   // Points to a 2D array of values holding the board
  int dimension; // Tells parsers how long each row and column are (will be 9 for this project)
} sudoku_t;
```

### Testing plan

**Unit testing** - A small test program in `testing.sh` to test each module to make sure it does what it's supposed to do. This includes, but is not limited to, error checking, such as providing the *solver* with sudoku boards without solutions and/or with non-unique solutions.

**Integration testing** - We will take known sudoku boards and run them through the *solver*, and then check the output against the valid solutions that we know to be true. Once this is done, we will also test the *create* functionality using the *solver* module, which we can run generated sudoku boards through to make sure they are valid.

**Fuzztesting** - We will create a program that continuously generates sudoku boards using the *create* functionality and then runs these through the *solver*. If any boards are labeled invalid by the *solver* we will check them manually to determine if the error is within the *create* or *solve* functional modules.
