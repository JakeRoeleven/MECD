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
	char *rank;
	char *NameP; 
	Date DOB; 
	int currentlyActive;
	char *currentDeployment;
	char *militaryID;
};

char* getFileHeader();
void writeRecordToFile(Record record, char*inFileName); 
void readFile();
void writeHeader(char *inFileName);
void filterHeader(char *str);
void addRecord(char *inFileName);
int getStrLen(char str[1024]);
void displayFile(char *str);
void printHeader();
void buildRecord();

#endif