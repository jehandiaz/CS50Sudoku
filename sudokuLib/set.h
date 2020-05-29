/*
 * Author: Team Rocket
 * CS50, Spring 2020
 * 
 * A set is an unordered collection of (key, item) pairs
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef __SET_H
#define __SET_H

/*************** global types ***************/
typedef struct set set_t;

/*************** functions *****************/
/************** set_new **************/
/* Create a new (empty) set.
 * 
 * We return:
 *   pointer to a new set, or NULL if error.
 * We guarantee:
 *   The set is initialized empty.
 * Caller is responsible for:
 *   later calling set_delete.
 */
set_t *set_new(void);

/**************** set_insert ****************/
/* Insert item, identified by a key (int), into the given set.
 *
 * Caller provides:
 *   valid set pointer and valid int pointer
 * We return:
 *  false if key exists, any parameter is NULL, or error;
 *  true iff new item was inserted and initialized to false bool value
 * Caller is responsible for:
 *   later calling set_delete to free the memory used by key ints.
 */
bool set_insert(set_t *set, const int *key);

/**************** set_find ****************/
/* Return the bool associated with the given key.
 *
 * Caller provides:
 *   valid set pointer, valid string pointer.
 * We return:
 *   the bool value, if 
 *   NULL if set is NULL, key is NULL, or key is not found.
 * Notes:
 *   The item is *not* removed from the set.
 *   Thus, the caller should *not* free the pointer that is returned.
 */
void *set_find(set_t *set, const char *key);
