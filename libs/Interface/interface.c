/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 * 	Jake Roeleven - 13246638
 * 	Thomas Coates - 13276922
 * 	Beichen Man   - 12416780
 * 	Zinh AL-Sweedy - 12402677
 * Date Complete:
*******************************************************************************/

#include "interface.h"

void encryptAndCompressFile() {	
	char inFileName[1024];
    printf("Name the file you wish to encrypt and compress?\n");
    scanf("%s", inFileName);
    getchar();
    encryptFile(inFileName);
	Compress(inFileName);
	addFileToQueue(createFileRecord(inFileName, 1, 1));
}

void decryptAndDecompressFile() {	
	char inFileName[1024];
    printf("Name the file you wish to Decompress and decrypt?\n");
    scanf("%s", inFileName);
    getchar();
	Decompress(inFileName);
	decryptFile(changeFileExtension(inFileName));
	addFileToQueue(createFileRecord(inFileName, 0, 0));
}

void compressOnly() {
	
	char inFileName[1024];
    printf("Name the file you wish to compress?\n");
    scanf("%s", inFileName);
	Compress(inFileName);
	addFileToQueue(createFileRecord(inFileName, 0, 1));

}

void decompressOnly() {
	char inFileName[1024];
    printf("Name the file you wish to decompress?\n");
    scanf("%s", inFileName);
	Decompress(inFileName);
	addFileToQueue(createFileRecord(inFileName, 0, 0));
}

void encryptOnly() {
	char inFileName[1024];
    printf("Name the file you wish to encrypt?\n");
    scanf("%s", inFileName);
	encryptFile(inFileName);
	addFileToQueue(createFileRecord(inFileName, 1, 0));
}

void decryptOnly() {
	char inFileName[1024];
    printf("Name the file you wish to decrypt?\n");
    scanf("%s", inFileName);
	decryptFile(inFileName);
	addFileToQueue(createFileRecord(inFileName, 0, 0));
}

void createRecords() {
	char inFileName[1024];
	printf("What would you like to name the file: ");
    scanf("%s", inFileName);
    strcat(inFileName, ".txt");
    buildRecord(inFileName);
	addFileToQueue(createFileRecord(inFileName, 0, 0));
}

void displayRecords() {
	addFileToQueue(createFileRecord(readFile(), 0, 0));
}

char* changeFileExtension(char* fileNameP) {
    size_t nameLength = strlen(fileNameP);
    fileNameP[4 <= nameLength ? nameLength-4 : 0] = '\0';
    strcat(fileNameP, ".txt");
    return fileNameP;
}

void addFileToQueue(FileRecord record) {
	FILE *recentFileP;
	recentFileP = fopen("fileDatabase.txt", "a+");
	fwrite(&record, sizeof(FileRecord), 1, recentFileP);
	fclose(recentFileP);
}

FileRecord createFileRecord(char *inFileName, int encrypted, int compressed) {
	FileRecord filerecord;
	int i;
	strcpy(filerecord.FileName, inFileName);
	filerecord.encrypted = encrypted;
	filerecord.compressed = compressed;
	return filerecord;
}

void viewFileDatabase() {

	VECTOR(recentRecords);
	FILE *recentFileP;
	FileRecord record[20];
	int recordsRead = 0, i;

    recentFileP = fopen("fileDatabase.txt", "r");
   
	
    /*Check if the database is null, throw and error and return 0*/
    if (recentFileP == NULL) {
		printf("Read error: Did you delete the database file?\n\n\n");
		exit(0);
	}
    
    while (fread (&record[recordsRead], sizeof(FileRecord), 1, recentFileP) && recordsRead < 20) {
    	VECTOR_PUSHBACK(recentRecords, &record[recordsRead]);
    	recordsRead++;
    }
    fclose(recentFileP);

    displayRecordHeader();
    for (i = 0; i < VECTOR_SIZE(recentRecords); i++) {
	    displayRecord(*VECTOR_AT(recentRecords, FileRecord *, i));
	}
	printf("--------------1 = TRUE, 0 = FALSE-------------------\n");
}

void displayRecord(FileRecord fileRecord) {
	printf("%-31s %d %9d\n", fileRecord.FileName, fileRecord.encrypted, fileRecord.compressed);
}

void displayRecordHeader() {
	printf("---------------RECENT FILES ACCESSED----------------\n");
	printf("FILE NAME                       ENCRYPTED COMPRESSED\n");
    printf("----------------------------------------------------\n");
}
