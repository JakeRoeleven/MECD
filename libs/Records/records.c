/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * 
 * Record System
 * 
 * Author:
 * 	Jake Roeleven - 13246638
 * Date Complete:
 * 	9/10/2019
*******************************************************************************/

/* Inclusions */
#include "records.h"

/* Function that controls how many records to write at a time */
void buildRecord(char *inFileNameP) {
	int i = 1;
    writeHeader(inFileNameP);
    while (i == 1) {
    	printf("Add a new record (1 for Yes, O for No): ");
    	scanf("%d", &i);
    	/* Remove trailing /n character*/
    	getchar();

    	if (i == 1) addRecord(inFileNameP);
    }
    printf("Success! Your file can be found at %s!\n", inFileNameP);
}

/* Instatiate a new record instance, write each field, the write
each record to a file. This caused major issues when switching ot linux can
definetly be done more effeciently but at least it works */
void addRecord(char *inFileNameP) {

	/* Instatiate a record */
	Record *record = (Record *) malloc(sizeof(Record));

	/* Write the name */
	char nameBuffer[65];
	memset(record->NameP,0,sizeof(record->NameP));
	printf("\nEnter first name, last name seperated by a space: ");
	if (fgets(nameBuffer, sizeof nameBuffer, stdin) != NULL) {
	  size_t len = strlen(nameBuffer);
	  if (len > 0 && nameBuffer[len-1] == '\n') {
	    nameBuffer[--len] = '\0';
	  }
	}
	strncpy(record->NameP, nameBuffer, (strlen(nameBuffer)));
	memset(nameBuffer,0,sizeof(nameBuffer));
	fflush(stdin);
	
	/* Write the rank */
	char rankBuffer[65];
	memset(record->rank,0,sizeof(record->NameP));
	printf("Enter rank: ");
	if (fgets(rankBuffer, sizeof rankBuffer, stdin) != NULL) {
	  size_t len = strlen(rankBuffer);
	  if (len > 0 && rankBuffer[len-1] == '\n') {
	    rankBuffer[--len] = '\0';
	  }
	}
	strncpy(record->rank, rankBuffer, strlen(rankBuffer));
	memset(rankBuffer,0,sizeof(rankBuffer));
	fflush(stdin);

	/* Write the military ID */
	char militaryBuffer[65];
	printf("Enter Military ID: ");
	memset(record->militaryID,0,sizeof(record->militaryID));
	if (fgets(militaryBuffer, sizeof militaryBuffer, stdin) != NULL) {
	  size_t len = strlen(militaryBuffer);
	  if (len > 0 && militaryBuffer[len-1] == '\n') {
	    militaryBuffer[--len] = '\0';
	  }
	}
	strncpy(record->militaryID, militaryBuffer, strlen(militaryBuffer));
	fflush(stdin);
	memset(militaryBuffer,0,sizeof(militaryBuffer));

	/* Write the data of birth */
	printf("Enter Date of Birth. ");
	printf("Enter month, date and year seperated by spaces: ");
	scanf("%d %d %d", &record->DOB.day
			, &record->DOB.month
			, &record->DOB.year);
	getchar();
	
	/* Write there active status */
	printf("Are they Currently Active (Enter 1 For Yes, 0 For No): ");
	scanf("%d", &record->currentlyActive);
	getchar();

	/* Write where they are currently deployed */
	char deploymentBuffer[65];
	memset(record->currentDeployment,0,sizeof(record->currentDeployment));
	printf("What location are they Currently Deployed: ");
	if (fgets(deploymentBuffer, sizeof deploymentBuffer, stdin) != NULL) {
	  size_t len = strlen(deploymentBuffer);
	  if (len > 0 && deploymentBuffer[len-1] == '\n') {
	    deploymentBuffer[--len] = '\0';
	  }
	}
	strncpy(record->currentDeployment, deploymentBuffer, 
		strlen(deploymentBuffer));
	memset(deploymentBuffer,0,sizeof(deploymentBuffer));
	fflush(stdin);

	/* Print the record you are about to add*/
	printf("\nAdding Record: %s %s %s %d-%d-%d %d %s\n\n", 
    	record->rank, record->NameP, record->militaryID, 
    	record->DOB.day, record->DOB.month, record->DOB.year,
    	record->currentlyActive, record->currentDeployment);
	
	/* Add the record */
	writeRecordToFile(record, inFileNameP);
	
	free(record);
}

/* Write the file header to the file. Purpose explained below */
void writeHeader(char *inFileNameP) {
    FILE *fileP;
    fileP = fopen(inFileNameP, "w"); 
    fprintf(fileP, "%s", getFileHeader());
    fclose(fileP);
}

/* Append the passed in record to the file*/
void writeRecordToFile(Record *record, char *inFileNameP) {
    FILE *fileP;
    /* Use "a+" mode to append rather then overwrite the file*/
    fileP = fopen(inFileNameP, "a+"); 
    fprintf(fileP, "%s %s %s %d-%d-%d %d %s\n", 
    	record->rank, record->NameP, record->militaryID,  
    	record->DOB.day, record->DOB.month, record->DOB.year,
    	record->currentlyActive, record->currentDeployment);
    fclose(fileP);
}

/*The File Header is placed at the top of every file created. It servers two
purposes: 1 only allow the program to interact with files that contain the 
header increasing security of the system and 2 compression is only effective 
with files over a certain size, the file header is in place to demonstrate 
how compression effectivley */
char *getFileHeader() { 
	char *headerInfoP = ("-----------------------------------------------------"
						"--------------------------------------\n"
						"------------------------------------MECD DATABASE FILE"
						"-------------------------------------\n"
						"------------------------------------------------------"
						"-------------------------------------\n"
						"This military record was built with the military compr"
						"ession and encryption database (MCED)\n"
						"----This is for confidential viewing of authorised per"
						"sonel only, do not let other see!----\n"
						"--------This file can only be accessed using the MCED "
						"utility command line program!--------\n"
						"------------------------Thank you for using the MCED u"
						"tility.------------------------------\n"
						"--------------------For more info go to: https://githu"
						"b.com/JakeRoeleven/FundOfC-----------\n"
						"------------------------------------------------------"
						"-------------------------------------\n"
						"----------------------------DO NOT USE WITH ANY OTHER "
						"PROGRAM------------------------------\n"
						"------------------------------------------------------"
						"-------------------------------------\n"
						"------------------------------------------------------"
						"-------------------------------------\n"
						"----------------------COPYRIGHT 2019 DO NOT USE WITHOU"
						"T PERMISSION-------------------------\n"
						"------------------------------------------------------"
						"-------------------------------------\n");
	return headerInfoP;
}

/*Read in a MECD file and display its conetents*/
char *readFile() {
	char inFileName[1024];
	char *fileBuffer = 0;
    long length;

	printf("What file would you like to display: ");
    scanf("%s", inFileName);
    /* Clear left over end of line char */
    getchar();
    FILE * inFileP = fopen(inFileName, "rb");
    
    if (inFileP == NULL) {
        printf("Error: File not found!\n\n");
        exit(0);
    }

    if (inFileP) {
      fseek (inFileP, 0, SEEK_END);
      length = ftell(inFileP);
      fseek (inFileP, 0, SEEK_SET);
      fileBuffer = malloc(length);
      if (fileBuffer) {
        fread (fileBuffer, 1, length, inFileP);
      }
      fclose (inFileP);
    }

    displayFile(fileBuffer);
}

/*Check the file header is the same as the MECD file system and remove it*/
void filterHeader(char *fileString) {
	int i, headerLength;
	long fileLength = strlen(fileString);
	headerLength = strlen(getFileHeader());
	for (i = headerLength; i < fileLength; i++) {
		printf("%c", fileString[i]);
	}
}

/* Display file controller */
void displayFile(char *fileString) {
	printHeader();
	filterHeader(fileString);
	printf("--------------ACTIVE 1 = TRUE, 0 = FALSE------------------\n");
}

/* Formatting Header */
void printHeader() {
	printf("\n-----------------------MECD  RECORD-----------------------\n");
	printf("Rank   Name     ID   DOB   Active    Current    Deployment\n");
    printf("----------------------------------------------------------\n");
}

