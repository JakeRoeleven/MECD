/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * 
 * Huffman Compression
 * 
 * Author(s):
 * 	Jake Roeleven - 13246638
 * Date Complete:
 * 	30/05/2019
 * Notes: 
 * 	The follwoing refrences were used to help complete this algorithm:
 *  - https://en.wikipedia.org/wiki/Huffman_coding
 *	- https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
 * 	- https://gitlab.com/mehalter/Huffman-Coding-C/blob/master/huffman.c
 * 	- https://github.com/DanielScocco/Simple-Huffman-Coding/blob/master/huffman.c
*******************************************************************************/

#ifndef COMPRESSION
#define COMPRESSION

/* Inclusions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definitions */
#define MAX_CHAR_RANGE 257   
#define EOF_FLAG 256    
#define CHAR_BIT_SIZE 8

/*Structs*/
typedef struct HuffmanNode Node; 

struct HuffmanNode {
    int contents;
    int frequency;
    Node *leftP, *rightP;
};

/*Function Prototypes*/
void Compress();
void Decompress();

Node *buildHuffmanTree(int frequenciesArray[]);
char **buildCharacterTable( int frequenciesArray[]);

void searchHuffmanTree(Node *treeP, char **tableP, char *toFindP);
int compareNodes(const void *nodeOneP, const void *nodeTwo);

void writeFileHeader(FILE *outFile, int frequenciesArray[]);
int *readFileHeader(FILE *inFile);

void encodeBit(const char *bitArrayP, FILE *outFileP);
int decodeBit(FILE *inFileP);
int bitToChar(FILE *inFileP, Node *treeP);
char *concatSuffix(char *currentP, char suffix);

void encodeFile(FILE *in, FILE *out);
void decodeFile(FILE *in, FILE *out);

void freeHuffmanTree(Node *treeP);
void freeTable(char *tableP[]);

char* removeFileExtension(char* str);
void deleteFile(char* inFileName);
long int findFileSize(FILE *inFileP);
void printFileStats(long int inFileSize, long int outFileSize);
void printCompress();



#endif
