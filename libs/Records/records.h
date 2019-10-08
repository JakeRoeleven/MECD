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

/*Packages*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

char *getFileHeader();
void writeRecordToFile(Record *record, char*inFileName); 
char *readFile();
void writeHeader(char *inFileName);
void filterHeader(char *str);
void addRecord(char *inFileName);
int getStrLen(char str[1024]);
void displayFile(char *str);
void printHeader();
void buildRecord(char *inFileName);

#endif