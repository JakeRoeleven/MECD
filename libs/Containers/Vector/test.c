/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 *     Jake Roeleven
 * Comments:
 *     Test File for the Vector Data Structure
 *     gcc -Wall -ansi -o test.out vector.h vector.c test.c -lm
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

int main(void)
{
    VECTOR(v);
    int i;

    VECTOR_PUSHBACK(v, "Hi");
    VECTOR_PUSHBACK(v, "my");
    VECTOR_PUSHBACK(v, "name");
    VECTOR_PUSHBACK(v, "is");
    VECTOR_PUSHBACK(v, "Jake");

    for (i = 0; i < VECTOR_SIZE(v); i++)
        printf("%s ", (char *) VECTOR_AT(v, char*, i));
    printf("\n");

    VECTOR_SET(v, 4, "Kevin");

    for (i = 0; i < VECTOR_SIZE(v); i++)
        printf("%s ", (char *) VECTOR_AT(v, char*, i));
    printf("\n");

    VECTOR_DELETE(v, 3);

    for (i = 0; i < VECTOR_SIZE(v); i++)
        printf("%s ", (char *) VECTOR_AT(v, char*, i));
    printf("\n");

    VECTOR_POPBACK(v);

    for (i = 0; i < VECTOR_SIZE(v); i++)
        printf("%s ", (char *) VECTOR_AT(v, char*, i));
    printf("\n");

    return 0;
}