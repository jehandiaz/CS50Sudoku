---
layout: page
title: Team Rocket Sudoku Design Spec
---

Sudoku is well known logic puzzle where numbers between 1 and 9 are placed on a 9x9 grid of cells. The placement of numbers has to follow certain rules. There are many variations of Sudoku, but for this project you will be looking at only the most common version of Sudoku. In this version the 9x9 grid is further divided into 9 square shaped regions of size 3x3 as shown below.

A Design Spec should contain several sections:

* User interface
* Inputs and Outputs
* Functional decomposition into modules
* Pseudo code for logic/algorithmic flow
* Dataflow through modules
* Major data structures
* Testing plan

Let's look through each.

### User interface

The Sudoku's only interface with the user is on the command-line; it must always have one arguments.

```
sudoku action
```

For example:

``` bash
$ ./sudoku create
$ ./sudoku solve
```

### Inputs and outputs

Input: the only inputs are command-line parameters; see the User Interface above.

Output: If "create" is given as command-line argument, a 9x9 sudoku puzzle with empty spaces is displayed in stdout. If "solve" is given as command-line argument, the sudoku puzzle just outputted by "create" is solved then outputted to stdout. The sudoku puzzle is represented as 9 lines in the following format, where zeroes imply empty slots:

 * 1 2 3 4 5 6 7 8 9
 * 1 0 2 3 0 9 1 2 4

### Functional decomposition into modules

We anticipate the following modules or functions: (specift which are create and which are solve)

 1. *main*, which parses arguments and initializes other modules
 2. *createGrid*
 3. *fillNumbers* 
 4. *removeNumbers* which takes complete puzzle, removes values, and makes sure solution is still unique for each removed value
 5. *checkUnique* which checks to make sure a given puzzle has only one solution
 6. *printPuzzle* which prints a given puzzle to stdout
 7. *validatePuzzle* 
 8. 


And some helper modules that provide data structures:

 1. *bag* of pages we have yet to explore
 4. *hashtable* of URLs we've seen so far

### Pseudo code for logic/algorithmic flow

The crawler will run as follows:

1. execute from a command line as shown in the User Interface
2. parse the command line, validate parameters, initialize other modules
3. 

A good implementation will not necessarily encode all the above code in a single, deeply-nested function; part of the Implementation Spec is to break the pseudocode down into a cleanly arranged set of functions.

Notice that our pseudocode says nothing about the order in which it crawls webpages; since it presumably pulls them out of a *bag*, and a *bag* abstract data structure explicitly denies any promise about the order of items removed from a bag, we can't expect any particular crawl order.
That's ok.
The result may or may not be a Breadth-First Search, but for the crawler we don't care about the order as long as we explore everything within the `maxDepth` neighborhood.

The crawler completes and exits when it has nothing left in its bag - no more pages to be crawled.
The maxDepth parameter indirectly determines the number of pages that the crawler will retrieve.


### Dataflow through modules

 1. *main* parses parameters and passes them to the crawler.
 2. *crawler* uses a bag to track pages to explore, and hashtable to track pages seen; when it explores a page it gives the page URL to the pagefetcher, then the result to pagesaver, then to the pagescanner.
 3. *pagefetcher* fetches the contents (HTML) for a page from a URL and returns.
 4. *pagesaver* outputs a page to the appropriate file.
 4. *pagescanner* extracts URLs from a page and returns one at a time.

### Major data structures

Three helper modules provide data structures:

 1. *bag* of page (URL, depth) structures
 2. *set* of URLs (indirectly used by hashtable)
 4. *hashtable* of URLs

### Testing plan

*Unit testing*.  A small test program in `testing.sh` to test each module to make sure it does what it's supposed to do.

*Integration testing*.  Assemble the crawler and test it as a whole using `testing.sh`.
In each case, examine the output files carefully to be sure they have the contents of the correct page, with the correct URL, and the correct depth.
Ensure that no pages are missing or duplicated.
Print "progress" indicators from the crawler as it proceeds (e.g., print each URL explored, and each URL found in the pages it explores) so you can watch its progress as it runs.

0. Test the program with various forms of incorrect command-line arguments to ensure that its command-line parsing, and validation of those parameters, works correctly.

0. Test the crawler with a `seedURL` that points to a non-existent server.

0. Test the crawler with a `seedURL` that points to a non-internal server.

0. Test the crawler with a `seedURL` that points to a valid server but non-existent page.

1. Crawl a simple, closed set of cross-linked web pages to crawl.
Ensure that some page(s) are mentioned multiple times within a page, and multiple times across the set of pages.
Ensure there is a loop (a cycle in the graph of pages).
In such a little site, you know exactly what set of pages should be crawled, at what depths, and you know where your program might trip up.

2. Point the crawler at a page in that site, and explore at depths 0, 1, 2, 3, 4, 5.
Verify that the files created match expectations.

2. Repeat with a different seed page in that same site.
If the site is indeed a graph, with cycles, there should be several interesting starting points.

3. Point the crawler at our Wikipedia playground.
Explore at depths 0, 1, 2.
(It takes a long time to run at depth 2 or higher!) Verify that the files created match expectations.

5. When you are confident that your crawler runs well, test it on a part of our playground or with a greater depth - but be ready to kill it if it seems to be running amok.
