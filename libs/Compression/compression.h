/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 * 	Jake Roeleven
 * Date Complete:
*******************************************************************************/

#ifndef COMPRESSION_H
#define COMPRESSION_H

typedef struct HuffmanNode Node; 
typedef struct HuffmanTree Tree;

struct HuffmanNode {
    int* contents;
    int size, freq;
    Node* left;
    Node* right;
};

struct HuffmanTree {
    Node** nodes;
    int size;
};

Node* createNode(int *nodeContentsP, int nodeSize, int nodeFreq, Node* leftP, Node* rightP); 
Node* createBaseNode(int *nodeContentsP, int freq);
Node* buildTree(Tree* treeList);
char** generateBitAsciiArray(Node* tree);
char* getCode(Node* next, int find, char* bits);
int* getSmallest(Tree* frequencies);

Tree* readFrequencyFile(char* filePath);
Tree* buildFrequencyFile(char* filePath, char* outputPath);
Tree* arrayFromList(int* list, int size);

void freeTree(Node* tree);
void freeNodeArray(Tree* tree);
void freeBitArray(char** arr);

void compression(char* inputPath, char* outputPath, char** array);
void decompressFile(char* inputPath, char* outputPath,  Node* tree, int size);

void compressFile();

#endif
