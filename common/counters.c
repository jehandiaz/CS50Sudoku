/* 
 * counters.c - Sudoku set module
 * implements methods from set.h 
 * Author: Team Rocket
 * CS50, Spring 2020
 * A counterset is a collection of (key, count) pairs, where key is a number between 
 * 1 and 9 and count indicates whether the key has been seen or not
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "counters.h"

/************* local types **************/
typedef struct counter {
	int key; // the key for this counter 
	int count; // pointer to the data for this item which is the counter value
	struct counter *next; // link to the next node/ key in the counterset
} counter_t;	
/************* global types *************/
typedef struct counters {
        struct counter *head;  // head of the set of keys in the counterset
} counters_t;

/************ global functions ***********/

/************ local functions ************/ 
/* not visible outside of this file */

static counter_t *counter_new(int key, int count);

/************ counters_new() ************/
counters_t *counters_new(void) {
	counters_t *counterset = malloc(sizeof(counters_t));

	if (counterset == NULL) {
	return NULL; // error allocating counterset
	} else {
		counterset->head = NULL;
 		return counterset;
	}
}

/******************* counter_new ****************/
/* Allocate and initialize a counter */
static counter_t* counter_new(const int key, const int count)
{
	counter_t *ctr = malloc(sizeof(counter_t));

	if (ctr == NULL) {
		return NULL;
	} else {
		ctr->key = key;
		ctr->count = count;
		ctr->next = NULL;
		return ctr;
	}
}

/************* counters_add() ****************/
void counters_add(counters_t *ctrs, const int key) {

	if (ctrs != NULL && key >= 0) {
		counter_t *new = counter_new(key, 1);
		if (new != NULL) {
			// add counter to the head of the set
			new->next = ctrs->head;
			ctrs->head = new;
			return;
		}
	}
	return;
}

/*************** counters_get() *******************/
int counters_get(counters_t *ctrs, const int key) {
	if (ctrs != NULL && key >= 0)
	{
		counter_t *current = ctrs->head;
	        while (current != NULL) {
	       		if (current->key == key) {
				return current->count;
			} else {
				current = current->next;
			}
	       }
	}
	return 0;
}

/*************** counters_delete() *********************/
void counters_delete(counters_t *ctrs){
	if (ctrs != NULL) {
		for (counter_t *ctr = ctrs-> head; ctr != NULL; ) {
			counter_t *next = ctr->next;
			free(ctr);
			ctr = next;
		}
		free(ctrs);
		ctrs = NULL;
	}
}