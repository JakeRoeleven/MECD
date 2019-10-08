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
#include "../Encryption/encryption.h"
#include "../Records/records.h"
#include "../Containers/Vector/vector.h"

typedef struct FileRecord FileRecord;

struct FileRecord {
	char FileName[64];
	int encrypted;
	int compressed;
};

char* changeFileExtension(char* fileName);
void addFileToQueue(FileRecord record);
FileRecord createFileRecord(char *inFileName, int encrypted, int compressed);
void encryptAndCompressFile();
void decryptAndDecompressFile();
void compressOnly();
void decompressOnly();
void encryptOnly();
void createRecords();
void decryptOnly();
void viewFileDatabase();
void displayRecord(FileRecord fileRecord);
void displayRecordHeader();