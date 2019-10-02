
#include "../Compression/compression.h"
#include "../Encryption/encryption.c"

void encryptAndCompressFile() {	
	char inFileName[1024];
    printf("Name the file you wish to encrypt and compress?\n");
    scanf("%s", inFileName);
	Compress(inFileName);
	encryptFile(inFileName);
}

void decryptAndDecompressFile() {	
	char inFileName[1024];
    printf("Name the file you wish to encrypt and compress?\n");
    scanf("%s", inFileName);
	Decompress(inFileName);
	decryptFile(inFileName);
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