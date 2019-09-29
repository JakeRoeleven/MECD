/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 * 	Jake Roeleven
 * Date Complete:
*******************************************************************************/

#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR  257   
#define EOF_FLAG    256    
#define CHAR_BIT_SIZE   8

/*Structs*/
typedef struct HuffmanNode Node; 

struct HuffmanNode {
    int contents;
    int frequency;
    Node *leftP, *rightP;
};

Node *buildHuffmanTree(int frequenciesArray[]);
int compareNodes(const void *nodeOneP, const void *nodeTwo);
char **buildCharacterTable( int frequenciesArray[]);

void searchHuffmanTree(Node *treeP, char **tableP, char *toFindP);
char *addPrefix(char *current, char prefix);

void writeFileHeader(FILE *outFile, int frequenciesArray[]);
int *readFileHeader(FILE *inFile);

void encodeBit(const char *bitArrayP, FILE *outFileP);
int decodeBit(FILE *inFileP);
int bitToChar(FILE *inFileP, Node *treeP);
void freeHuffmanTree(Node *treeP);
void freeTable(char *tableP[]);
void encodeFile(FILE *in, FILE *out);
void decodeFile(FILE *in, FILE *out);


#endif
