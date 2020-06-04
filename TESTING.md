TESTING for sudoku.c

Team Rocket
Spring 2020

## Testing of the program: 

In order to test all our modules, we performed the following tests:

* *Argument error checking* Testing the program with different types of invalid arguments. e.g. incorrect number of arguments, arguments different from `solve` and `create`.

* *Integration testing*. Assemble all the modules and test it as a whole using `testing.sh`. We provide different input files to test the solver. The reviewer can also use their own input files if they desire to.

* *Unit testing*. for *create*  and *solve*.

* *Fuzz testing* Use the provided `fuzztest.c` to test `sudoku solve`. Our `fuzztest.c` takes a number as argument and creates that many random puzzles, gives them to the solver, and prints the number of puzzles that were successfully solved.


These tests can be found in `testing.sh`

The output can be found in `testing.out`

## Test run

An example test run is stored in `testing.out`, built with

`make test`

In that file one can see the command lines used for specific tests along with their output. 

## Limitations

- We assume that the file provided to `solve` contains a valid sudoku puzzle.