
#include "../Compression/compression.h"
/*#include "../Encryption/encryption.c"*/

void encryptAndCompressFile() {	

}

void compressOnly() {
	
	char inFileName[1024];
    printf("Name the file you wish to compress?\n");
    scanf("%s", inFileName);
	Compress(inFileName);

}

void decompressOnly() {
	char inFileName[1024];
    printf("Name the file you wish to compress?\n");
    scanf("%s", inFileName);
	Decompress(inFileName);
}