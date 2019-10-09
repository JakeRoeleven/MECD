/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 * 	Jake Roeleven - 13246638
 * 	Thomas Coates - 13276922
 * 	Beichen Man   - 12416780
 * 	Zinh AL-Sweedy - 12402677
 * Date Complete:
 * 	8/10/2019
*******************************************************************************/

/*Inclusions*/
#include "interface.h"

/*Calls the encryption and compression algorithms in order*/
void encryptAndCompressFile() {	
	char inFileName[1024];
    printf("Name the file you wish to encrypt and compress?\n");
    scanf("%s", inFileName);
    /* Clear line ending stuck in buffer*/
    getchar();
    encryptFile(inFileName);
	Compress(inFileName);
	/* Add file to the file managment system) */
	addFileToQueue(createFileRecord(inFileName, 1, 1));
}

/* Calls the decompession and decryption algorithms in order */
void decryptAndDecompressFile() {	
	char inFileName[1024];
    printf("Name the file you wish to Decompress and decrypt?\n");
    scanf("%s", inFileName);
    /* Clear line ending stuck in buffer*/
    getchar();
	Decompress(inFileName);
	decryptFile(changeFileExtension(inFileName));
	/* Add file to the file managment system) */
	addFileToQueue(createFileRecord(inFileName, 0, 0));
}

/* Only compresses the file */
void compressOnly() {
	char inFileName[1024];
    printf("Name the file you wish to compress?\n");
    scanf("%s", inFileName);
	Compress(inFileName);
	/* Add file to the file managment system) */
	addFileToQueue(createFileRecord(inFileName, 0, 1));
}

/* Only Decompresses the file */
void decompressOnly() {
	char inFileName[1024];
    printf("Name the file you wish to decompress?\n");
    scanf("%s", inFileName);
	Decompress(inFileName);
	/* Add file to the file managment system) */
	addFileToQueue(createFileRecord(inFileName, 0, 0));
}

/* Only encrypts the file */
void encryptOnly() {
	char inFileName[1024];
    printf("Name the file you wish to encrypt?\n");
    scanf("%s", inFileName);
	encryptFile(inFileName);
	/* Add file to the file managment system) */
	addFileToQueue(createFileRecord(inFileName, 1, 0));
}

/* Only decrypts the file */ 
void decryptOnly() {
	char inFileName[1024];
    printf("Name the file you wish to decrypt?\n");
    scanf("%s", inFileName);
	decryptFile(inFileName);
	/* Add file to the file managment system) */
	addFileToQueue(createFileRecord(inFileName, 0, 0));
}

/* Calls the create record function passing in the file name*/
void createRecords() {
	char inFileName[1024];
	printf("What would you like to name the file: ");
    scanf("%s", inFileName);
    strcat(inFileName, ".txt");
    buildRecord(inFileName);
    /* Add file to the file managment system) */
	addFileToQueue(createFileRecord(inFileName, 0, 0));
}

/* Calls the display record function*/
void displayRecords() {
	readFile();
}

/*This function removes the last 4 letters of a string, which is used to 
remove the file extension*/
char* changeFileExtension(char* fileNameP) {
    size_t nameLength = strlen(fileNameP);
    fileNameP[4 <= nameLength ? nameLength-4 : 0] = '\0';
    strcat(fileNameP, ".txt");
    return fileNameP;
}

/*************************File Managment System********************************/

/*Add a file to the queue*/
void addFileToQueue(FileRecord record) {
	FILE *recentFileP;
	recentFileP = fopen("fileDatabase.txt", "a+");
	fwrite(&record, sizeof(FileRecord), 1, recentFileP);
	fclose(recentFileP);
}

/*Create a file record based on the passed in parameters*/
FileRecord createFileRecord(char *inFileName, int encrypted, int compressed) {
	FileRecord filerecord;
	int i;
	strcpy(filerecord.FileName, inFileName);
	filerecord.encrypted = encrypted;
	filerecord.compressed = compressed;
	return filerecord;
}

/*View the file database. This function makes use of the VECTOR data structure
as to allow for dynamic memory managment*/
void viewFileDatabase() {

	VECTOR(recentRecords);
	FILE *recentFileP;
	FileRecord record[100];
	int recordsRead = 0, i;

    recentFileP = fopen("fileDatabase.txt", "r");
   
	
    /*Check if the database is null, throw and error and return 0*/
    if (recentFileP == NULL) {
		printf("Read error: Did you delete the database file?\n\n\n");
		exit(0);
	}
    
    while (fread (&record[recordsRead], sizeof(FileRecord), 1, recentFileP) 
    	&& recordsRead < 100) {
    	VECTOR_PUSHBACK(recentRecords, &record[recordsRead]);
    	recordsRead++;
    }
    fclose(recentFileP);

    displayRecordHeader();

    for (i = (VECTOR_SIZE(recentRecords)-1); i > 0; i--) {
	    displayRecord(*VECTOR_AT(recentRecords, FileRecord *, i));
	}

	printf("--------------1 = TRUE, 0 = FALSE-------------------\n");
}

/*Print each record*/
void displayRecord(FileRecord fileRecord) {
	printf("%-31s %d %9d\n", fileRecord.FileName, fileRecord.encrypted, 
	fileRecord.compressed);
}

/*Display the file header*/
void displayRecordHeader() {
	printf("---------------RECENT FILES ACCESSED----------------\n");
	printf("FILE NAME                       ENCRYPTED COMPRESSED\n");
    printf("----------------------------------------------------\n");
}
