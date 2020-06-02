# Makefile for sudoku project
#
# Team Rocket, May 27, 2020

C = ./common

PROG = sudoku
OBJS = sudoku.o

LLIBS = $C/common.a

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$C

MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LLIBS) -o $(PROG)

.PHONY: lib test clean

lib:
	$(MAKE) -C common

fuzztest: fuzztest.o
	$(CC) $(CFLAGS) $^ $(LLIBS) -o $@

# test: $(PROG)
#         echo "Running testing.sh, logging to testing.out..."
#         bash -v testing.sh > /dev/null 2>&1
#         echo "Test completed. Results can be found within testing.out."

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f fuzztest
	$(MAKE) -C common clean
	rm -f core
