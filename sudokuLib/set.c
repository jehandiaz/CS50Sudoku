/* 
 * set.c - Sudoku set module
 * implements methods from set.h 
 * Author: Team Rocket
 * CS50, Spring 2020
 * A set is an unordered collection of (key, item) pairs, where the key is a number and the 
 * item is a bool value tracking whether a number has been used in the Sudoku grid
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"

typedef struct setnode {
  const int *key;
  bool isUsed;
  struct setnode *next;
} setnode_t;

typedef struct set {
  struct setnode *head;
} set_t;

set_t *set_new() {
	set_t *set = malloc(sizeof(set_t));
	if (set == NULL) {
		return NULL; // error allocating set
	} else {
		// initialize contents of set structure 
		set->head = NULL;
		return set;
	}
}

static setnode_t* setnode_new(const int *key)
{
	setnode_t *node = malloc(sizeof(setnode_t));

	if (node == NULL) {
		// error allocating memory for node; return error
		return NULL;
	} else {
		node->key = key;
		node->isUsed = false;
		node->next = NULL;
		return node;
	}
}