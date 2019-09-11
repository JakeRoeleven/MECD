/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 * 		Jake Roeleven
 * Comment:
 * 		A data container that allows for easy dynamic memory managment in C
 * 		Inspired by: 
 * 		C++ Vector Container: http://www.cplusplus.com/reference/vector/vector/
 * 		Edd Mans Vector Tutorial: https://eddmann.com/posts
 *								  /implementing-a-dynamic-vector-array-in-c/
*******************************************************************************/
/*Mutiple Inclusion Protection*/
#ifndef VECTOR_H
#define VECTOR_H
#define VECTOR_INITIAL_CAPACITY 4;

/*Function Macro Definitons*/
#define VECTOR(vec) vector vec; vector_init(&vec)
#define VECTOR_SIZE(vec) vector_size(&vec)
#define VECTOR_PUSHBACK(vec, item) vector_pushback(&vec, (void *) item)
#define VECTOR_POPBACK(vec) vector_popback(&vec)
#define VECTOR_AT(vec, type, id) (type) vector_at(&vec, id)
#define VECTOR_CLEAR(vec) vector_clear(&vec)
#define VECTOR_SET(vec, id, item) vector_set(&vec, id, (void *) item)
#define VECTOR_DELETE(vec, id) vector_delete(&vec, id)
#define VECTOR_EMPTY(vec) vector_empty(&vec)

/*Struct using double pointer to allow for any data type*/
typedef struct vector {
	void **items;
	int capacity;
	int count;
} vector;

/*Function prototypes*/
void vector_init(vector *);
int vector_size(vector *);
void vector_pushback(vector *, void *);
void vector_popback(vector *);
void *vector_at(vector *, int);
void vector_clear(vector *);
void vector_set(vector *, int index, void *item);
void vector_delete(vector *, int);
int vector_empty(vector *);

#endif

