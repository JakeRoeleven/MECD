/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 * 	Jake Roeleven - 13246638
 * 	Thomas Coates - 13276922
 * 	Beichen Man   - 12416780
 * 	Zinh AL-Sweedy - 12402677
 * Date Complete:
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Compression/compression.h"
#include "../Encryption/encryption.c"
#include "../Records/records.h"

char* changeFileExtension(char* fileName);

void encryptAndCompressFile() {	
	char inFileName[1024];
    printf("Name the file you wish to encrypt and compress?\n");
    scanf("%s", inFileName);
    getchar();
    encryptFile(inFileName);
	Compress(inFileName);
}

void decryptAndDecompressFile() {	
	char inFileName[1024];
    printf("Name the file you wish to Decompress and decrypt?\n");
    scanf("%s", inFileName);
    getchar();
	Decompress(inFileName);
	decryptFile(changeFileExtension(inFileName));
}

void compressOnly() {
	
	char inFileName[1024];
    printf("Name the file you wish to compress?\n");
    scanf("%s", inFileName);
	Compress(inFileName);

}

void decompressOnly() {
	char inFileName[1024];
    printf("Name the file you wish to decompress?\n");
    scanf("%s", inFileName);
	Decompress(inFileName);
}

void encryptOnly() {
	char inFileName[1024];
    printf("Name the file you wish to encrypt?\n");
    scanf("%s", inFileName);
	encryptFile(inFileName);
}

void decryptOnly() {
	char inFileName[1024];
    printf("Name the file you wish to decrypt?\n");
    scanf("%s", inFileName);
	decryptFile(inFileName);
}

void createRecords() {
	buildRecord();
}

void displayRecords() {
	readFile();
}

char* changeFileExtension(char* fileNameP) {
    size_t nameLength = strlen(fileNameP);
    fileNameP[4 <= nameLength ? nameLength-4 : 0] = '\0';
    strcat(fileNameP, ".txt");
    return fileNameP;
}