/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 * 	   Jake Roeleven
 * Comment:
 *     The libary functions included in the Vector Data Structure
 *     Read vector.h for more info
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

/*Defined here to allow for static use*/
static void vector_resize(vector *, int);

/*Like a constructor to initalise the vector*/
void vector_init(vector *v) {
	v->capacity = VECTOR_INITIAL_CAPACITY;
	v->count = 0;
	v->items = malloc(sizeof(void *) * v->capacity);   
}

/*The number of elemenets the vector currently contains*/
int vector_size(vector *v) {
	return v->count;
}

/*Resize the vector as it grows out of its initial size*/
static void vector_resize(vector *v, int capacity) {
	void **items = realloc(v->items, sizeof(void *) * capacity);
	if (items) {
		v->capacity = capacity;
		v->items = items;
	}
}

/*Add item to the end of the vector*/
void vector_pushback(vector *v, void *item) {
    if (v->capacity == v->count)
        vector_resize(v, v->capacity * 2);
    v->items[v->count++] = item;
}

/*Remove item from the end of the vector*/
void vector_popback(vector *v) {
    int index = (v->count - 1), i;

    if (index < 0 || index >= v->count)
        return;

    v->items[index] = NULL;

    for (i = index; i < v->count - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }

    v->count--;

    if (v->count > 0 && v->count == v->capacity / 4)
        vector_resize(v, v->capacity / 2);
}

/*Get vector at the location in the index*/
void *vector_at(vector *v, int index) {
	if (index >= 0 && index < v->count)
        return v->items[index];
    return NULL;
}

/*Clear the momory space and contents of the vector*/
void vector_clear(vector *v)
{
    int i;
    if (v->count != 0) 
    	for (i = 0; i < (v->count+1); i++)
    		vector_popback(v);
    free(v->items);
}

/*Set a already defined member of the vector*/
void vector_set(vector *v, int index, void *item) {
    if (index >= 0 && index < v->count)
        v->items[index] = item;
}

/*Delete a member of the vector, resize of nessacary*/
void vector_delete(vector *v, int index) {
	int i;

    if (index < 0 || index >= v->count)
        return;

    v->items[index] = NULL;

    for (i = index; i < v->count - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }

    v->count--;

    if (v->count > 0 && v->count == v->capacity / 4)
        vector_resize(v, v->capacity / 2);
}

/*Check if vector is empty*/
int vector_empty(vector *v) {
	if (v->count == 0)
		return 1;
	return 0;
}