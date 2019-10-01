/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * 
 * Records 
 * 
 * Author(s):
 * 	Jake Roeleven - 13246638
 * Date Complete:
 * 
 * Notes: 
*******************************************************************************/

#ifndef RECORD
#define RECORD

/* Inclusions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MilitaryRecord Record;
typedef struct Date Date;

struct Date {
	int day;
	int month;
	int year;
};

struct MilitaryRecord {
	char *rank, *fNameP, *lNameP;
	int *militaryID[9];
	Date DOB; 
	int yearsInService;
	char *division;
	int currentlyActive;
	char* currentDeployment;
};

#endif