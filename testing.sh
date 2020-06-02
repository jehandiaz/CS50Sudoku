#!/bin/bash
# program name: testing.sh
# author name: Team Rocket
# date: May 6, 2020
# Summary: test for sudoku.c
#
# Output: Into a file called testing.out

# usage: bash -v testing.sh


###########################################
### Tests with invalid arguments
###########################################

# incorrect number of arguments
./sudoku

./sudoku good stuff hahaha

# invalid arguments
./sudoku nice

./sudoku team rocket

###########################################
### testing create
###########################################

# create at level 1
./sudoku create 1

# create at level 2
./sudoku create 2

# create at level 3
./sudoku create 3

# create at level 4
./sudoku create 4

# create at level 5
./sudoku create 5

# create at level oustide maximum range 5
./sudoku create 7

###########################################
### testing solve
###########################################

# test from a file piped from the command line
./sudoku solve < file1

# test from stdin input by the user
./sudoku solve

# test with non-unique grid
./sudoku solve < nonUniqueFile

# test with a unique grid
./sudoku solve < nonUniqueFile

# test with a file containing ingeters outside the range (1-9)  ?????
./sudoku solve < outsideRange

# test with a invalid board (containing characters, )
./sudoku solve < invalidBoard

###########################################
### fuzz testing
###########################################

# fuzz testing solve with 1000 boards
./fuzztest 1000


