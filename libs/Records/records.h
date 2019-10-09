/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * 
 * Record Managament  
 * 
 * Author(s):
 * 	Jake Roeleven - 13246638
 * Date Complete:
*	9/10/2019
*******************************************************************************/

/*Double Inclusion Guard*/
#ifndef RECORD
#define RECORD

/*Packages*/
#include <stdio.h>  /* printf,scanf ,fgets,fread,fwrite,stdin*/
#include <string.h> /* strlen, strcpy,strncpy,strcmp*/
#include <stdlib.h> /* sizeof,NULL */

/* Structs */
typedef struct MilitaryRecord Record;
typedef struct Date Date;

struct Date {
	int day;
	int month;
	int year;
};

struct MilitaryRecord {
	char rank[64];
	char NameP[64]; 
	Date DOB; 
	int currentlyActive;
	char currentDeployment[64];
	char militaryID[64];
};

/*Function Prototypes */
char *getFileHeader();
void writeRecordToFile(Record *record, char*inFileName); 
char *readFile();
void writeHeader(char *inFileName);
void filterHeader(char *str);
void addRecord(char *inFileName);
void displayFile(char *str);
void printHeader();
void buildRecord(char *inFileName);

#endif