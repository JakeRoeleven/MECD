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

#include "records.h"
#include "string.h"


void buildRecord(char *inFileName) {
	int i = 1;
    writeHeader(inFileName);
    while (i == 1) {
    	printf("Add a new record (1 for Yes, O for No): ");
    	scanf("%d", &i);
    	getchar();
    	if (i == 1) addRecord(inFileName);
    }
    printf("Success! Your file can be found at %s\n", inFileName);
}

void addRecord(char *inFileName) {

	Record *record = (Record *) malloc(sizeof(Record));

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
	fflush(stdin);
	
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
	fflush(stdin);
	memset(rankBuffer,0,sizeof(rankBuffer));



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



	printf("Enter Date of Birth. ");
	printf("Enter month, date and year seperated by spaces: ");
	scanf("%d %d %d", &record->DOB.day
			, &record->DOB.month
			, &record->DOB.year);
	getchar();
	
	printf("Are they Currently Active (Enter 1 For Yes, 0 For No): ");
	scanf("%d", &record->currentlyActive);
	getchar();

	char deploymentBuffer[65];
	memset(record->currentDeployment,0,sizeof(record->currentDeployment));
	printf("Where are they Currently Deployed: ");
	if (fgets(deploymentBuffer, sizeof deploymentBuffer, stdin) != NULL) {
	  size_t len = strlen(deploymentBuffer);
	  if (len > 0 && deploymentBuffer[len-1] == '\n') {
	    deploymentBuffer[--len] = '\0';
	  }
	}
	strncpy(record->currentDeployment, deploymentBuffer, strlen(deploymentBuffer));
	fflush(stdin);
	memset(deploymentBuffer,0,sizeof(deploymentBuffer));

	printf("Adding Record: %s %s %s %d-%d-%d %d %s\n\n", 
    	record->rank, record->NameP, record->militaryID, 
    	record->DOB.day, record->DOB.month, record->DOB.year,
    	record->currentlyActive, record->currentDeployment);
	writeRecordToFile(record, inFileName);
	free(record);
}

int getStrLen(char str[1024]) {
	int count = 0;
	while (str[count] != '\n') {
        count++;
    }
    return count;
}

void writeHeader(char *inFileName) {
    FILE *fileP;
    fileP = fopen(inFileName, "w"); 
    fprintf(fileP, "%s", getFileHeader());
    fclose(fileP);
}

void writeRecordToFile(Record *record, char *inFileName) {
    FILE *fileP;
    fileP = fopen(inFileName, "a+"); 
    fprintf(fileP, "%s %s %s %d-%d-%d %d %s\n", 
    	record->rank, record->NameP, record->militaryID,  
    	record->DOB.day, record->DOB.month, record->DOB.year,
    	record->currentlyActive, record->currentDeployment);
    fclose(fileP);
}

/*The File Header is placed at the top of every file created*/
char *getFileHeader() { 
	char *HeaderInfo = ("-------------------------------------------------------------------------------------------\n"
						"------------------------------------MECD DATABASE FILE-------------------------------------\n"
						"-------------------------------------------------------------------------------------------\n"
						"This military record was built with the military compression and encryption database (MCED)\n"
						"----This is for confidential viewing of authorised personel only, do not let other see!----\n"
						"--------This file can only be accessed using the MCED utility command line program!--------\n"
						"------------------------Thank you for using the MCED utility.------------------------------\n"
						"--------------------For more info go to: https://github.com/JakeRoeleven/FundOfC-----------\n"
						"-------------------------------------------------------------------------------------------\n"
						"----------------------------DO NOT USE WITH ANY OTHER PROGRAM------------------------------\n"
						"-------------------------------------------------------------------------------------------\n"
						"-------------------------------------------------------------------------------------------\n"
						"----------------------COPYRIGHT 2019 DO NOT USE WITHOUT PERMISSION-------------------------\n"
						"-------------------------------------------------------------------------------------------\n");
	return HeaderInfo;
}

char *readFile() {
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
	printf("\n--------------------------MECD RECORD---------------------\n");
	printf("Rank   Name     ID   DOB   Active    Current    Deployment\n");
    printf("----------------------------------------------------------\n");
}

