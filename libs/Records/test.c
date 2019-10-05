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
void writeToFile(Record record, char*inFileName); 
void readFile();
void writeFileHeader(char *inFileName);
void filterHeader(char *str);
void addRecord(char *inFileName);
int getStrLen(char str[1024]);
void displayFile(char *str);
void printHeader();
void buildRecord();

int main() {
	return 0;
}

void buildRecord() {
	char inFileName[1024];
	int i = 1;
	printf("What would you like to name the file: ");
    scanf("%s", inFileName);
    strcat(inFileName, ".txt");
    getchar();
    writeFileHeader(inFileName);
    while (i == 1) {
    	printf("Add a new record (1 for Yes, O for No): ");
    	scanf("%d", &i);
    	getchar();
    	if (i == 1) addRecord(inFileName);
    }
    printf("Success! Your file can be found at %s\n", inFileName);
}

void addRecord(char *inFileName) {

	Record record;

	char nameBuffer[1024];
	printf("\nEnter first name, last name seperated by a space: ");
	if (fgets(nameBuffer, sizeof nameBuffer, stdin) != NULL) {
	  size_t len = strlen(nameBuffer);
	  if (len > 0 && nameBuffer[len-1] == '\n') {
	    nameBuffer[--len] = '\0';
	  }
	}
	int nSize = getStrLen(nameBuffer);
	nSize--;
	char nameString[nSize];
	strncpy(nameString, nameBuffer, nSize);
	record.NameP = nameString;
	fflush(stdin);

	char rankBuffer[1024];
	printf("Enter rank: ");
	if (fgets(rankBuffer, sizeof rankBuffer, stdin) != NULL) {
	  size_t len = strlen(rankBuffer);
	  if (len > 0 && rankBuffer[len-1] == '\n') {
	    rankBuffer[--len] = '\0';
	  }
	}
	int rSize = getStrLen(rankBuffer);
	rSize--;
	char rankString[rSize];
	strncpy(rankString, rankBuffer, rSize);
	record.rank = rankString;
	fflush(stdin);

	char militaryBuffer[1024];
	printf("Enter Military ID: ");
	if (fgets(militaryBuffer, sizeof militaryBuffer, stdin) != NULL) {
	  size_t len = strlen(militaryBuffer);
	  if (len > 0 && militaryBuffer[len-1] == '\n') {
	    militaryBuffer[--len] = '\0';
	  }
	}
	int mSize = getStrLen(militaryBuffer);
	mSize--;
	char milString[mSize];
	strncpy(milString, militaryBuffer, mSize);
	record.militaryID = milString;
	fflush(stdin);


	printf("Enter Date of Birth. ");
	printf("Enter month, date and year seperated by spaces: ");
	scanf("%d %d %d", &record.DOB.day
					, &record.DOB.month
					, &record.DOB.year);
	getchar();
	
	printf("Are they Currently Active (Enter 1 For Yes, 0 For No): ");
	scanf("%d", &record.currentlyActive);
	getchar();

	char deploymentBuffer[1024];
	printf("Where are they Currently Deployed: ");
	if (fgets(deploymentBuffer, sizeof deploymentBuffer, stdin) != NULL) {
	  size_t len = strlen(deploymentBuffer);
	  if (len > 0 && deploymentBuffer[len-1] == '\n') {
	    deploymentBuffer[--len] = '\0';
	  }
	}
	int dSize = getStrLen(deploymentBuffer);
	dSize--;
	char depString[dSize];
	strncpy(depString, deploymentBuffer, dSize);
	record.currentDeployment = depString;
	fflush(stdin);

	printf("Adding Record: %s %s %s %d-%d-%d %d %s\n\n", 
    	record.rank, record.NameP, record.militaryID, 
    	record.DOB.day, record.DOB.month, record.DOB.year,
    	record.currentlyActive, record.currentDeployment);
	writeToFile(record, inFileName);
}

int getStrLen(char str[1024]) {
	int count = 0;
	while (str[count] != '\n') {
        count++;
    }
    return count;
}

void writeFileHeader(char *inFileName) {
    FILE *fileP;
    fileP = fopen(inFileName, "w"); 
    fprintf(fileP, "%s", getFileHeader());
    fclose(fileP);
}

void writeToFile(Record record, char *inFileName) {
    FILE *fileP;
    fileP = fopen(inFileName, "a+"); 
    fprintf(fileP, "%s %s %s %d-%d-%d %d %s\n", 
    	record.rank, record.NameP, record.militaryID, 
    	record.DOB.day, record.DOB.month, record.DOB.year,
    	record.currentlyActive, record.currentDeployment);
    fclose(fileP);
}

char* getFileHeader() { 
	char *HeaderInfo = ("-------------------------------------------------------------------------------------------\n"
						"This military record was built with the military compression and encryption database (MCED)\n"
						"This is for confidential viewing of authorised personel only!\n"
						"This file can only be accessed using the MCED utility\n"
						"Thank you for using the MCED utility.\n"
						"For more info go to: https://github.com/JakeRoeleven/FundOfC\n"
						"-------------------------------------------------------------------------------------------\n");
	return HeaderInfo;
}

void readFile() {
	char inFileName[1024];
	printf("What file would you like to display: ");
    scanf("%s", inFileName);
    getchar();
	char *buffer = 0;
    long length;
    FILE * inFileP = fopen(inFileName, "rb");
    
    if (inFileP == NULL) {
        printf("Error: File not found\n");
        exit(0);
    }

    if (inFileP) {
      fseek (inFileP, 0, SEEK_END);
      length = ftell(inFileP);
      fseek (inFileP, 0, SEEK_SET);
      buffer = malloc(length);
      if (buffer) {
        fread (buffer, 1, length, inFileP);
      }
      fclose (inFileP);
    }
    displayFile(buffer);
}

void filterHeader(char *str) {
	int i;
	long length = strlen(str);
	int headerLength = strlen(getFileHeader());
	for (i = headerLength; i < length; i++) {
		printf("%c", str[i]);
	}
}

void displayFile(char *str) {
	printHeader();
	filterHeader(str);
}

void printHeader() {
	printf("-----------------------MECD REORD------------------------\n");
	printf("Rank   Name   ID   DOB   Active    Current    Deployment\n");
    printf("--------------------------------------------------------\n");
}