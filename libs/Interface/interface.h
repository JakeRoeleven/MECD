/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 * 	Jake Roeleven - 13246638
 * 	Thomas Coates - 13276922
 * 	Beichen Man   - 12416780
 * 	Zinh AL-Sweedy - 12402677
 * Date Complete:
 *	8/10/2019
*******************************************************************************/

/*Double Inclusion Guards*/
#ifndef INTERFACE
#define INTERFACE

/*Inclusion*/
#include <stdio.h>  /* printf,scanf ,fgets,fread,fwrite,stdin*/
#include <string.h> /* strlen, strcpy,strncpy,strcmp*/
#include <stdlib.h> /* sizeof,NULL */
#include "../Compression/compression.h"
#include "../Encryption/encryption.h"
#include "../Records/records.h"
#include "../Containers/Vector/vector.h"

/* Structs*/
typedef struct FileRecord FileRecord;

struct FileRecord {
	char FileName[64];
	int encrypted;
	int compressed;
};

/* Function Prototypes */
char* changeFileExtension(char* fileName);
void addFileToQueue(FileRecord record);
FileRecord createFileRecord(char *inFileName, int encrypted, int compressed);
void encryptAndCompressFile();
void decryptAndDecompressFile();
void compressOnly();
void decompressOnly();
void encryptOnly();
void createRecords();
void displayRecords();
void decryptOnly();
void viewFileDatabase();
void displayRecord(FileRecord fileRecord);
void displayRecordHeader();

#endif