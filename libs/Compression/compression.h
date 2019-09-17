/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 * 	Jake Roeleven
 * Date Complete:
*******************************************************************************/

#ifndef COMPRESSION_H
#define COMPRESSION_H

typedef struct HuffmanNode {
    int* contents;
    int size, freq;
    struct Node* left, Node* right;
} Node;

typedef struct HuffmanTree {
    struct Heap** nodes;
    int size, capacity;
} Tree;

Node* createNode(int *nodeContentsp, int nodeSize, int nodeFreq, Node *leftp, Node *rightp); 
Node* createBaseNode(int *nodeContentsp, int freq);
Node




/**************** Example ****/



/*
 * getTree(struct NodeArray* freq) - constructs a tree from the passed
 * in NodeArray struct by organizing them by frequency counts
 * return - a node struct of the top most node in the tree
 */
struct Node* getTree(struct NodeArray* freq);

/*
 * getBitArray(struct Node* tree) - constructs a malloced array of every bit
 * pattern stored in the tree passed in
 * return - the malloced array that was created
 */
char** getBitArray(struct Node* tree);

/*
 * getCode(struct Node* next, int find, char* bits) - returns a malloced
 * string of the bits needed to code the character find. Takes in the node
 * struct of the tree, the int of the code you want to find, and NULL
 * as the char* bits to help with the recursive function
 * return - the malloced char* of the bit pattern needed to code the char find
 */
char* getCode(struct Node* next, int find, char* bits);

/*
 * getSmallest(struct NodeArray* frequencies) - returns a int array of size 2
 * containing the indexes of the 2 smallest nodes in the node array with a
 * frequency greater than 0
 * return - int* of the indexes of the 2 smallest non-zero frequency nodes
 */
int* getSmallest(struct NodeArray* frequencies);

/*
 * getFrequency(char* filePath) - creates a node array of base nodes and their
 * frequencies from the compressed file at 'filePath'
 * return - a NodeArray struct of the base nodes and their frequencies
 */
struct NodeArray* getFrequency(char* filePath);

/*
 * getFrequencyFile(char* filePath, char* outputPath) - calculates the character
 * frequencies of the given input file 'filePath' and either stores them into the
 * file 'outputPath', or does not write it to a file if the outputPath is NULL
 * return - a NodeArray struct of the base nodes and their frequencies
 */
struct NodeArray* getFrequencyFile(char* filePath, char* outputPath);

/*
 * arrayFromList(int* list, int size) - takes the given int array and converts
 * the values to an array of base nodes where there are 'size' characters with
 * non-zero values
 * return - a NodeArray struct of the base nodes and their frequencies
 */
struct NodeArray* arrayFromList(int* list, int size);

/*
 * encode(char* inputPath, char* outputPath, char** array) - takes the
 * file at 'inputPath' and converts each character to their corresponding
 * bit string and writes those bits to the file at 'outputPath' unless the
 * file is NULL, then the bits will be printed to the screen
 */
void encode(char* inputPath, char* outputPath, char** array);

/*
 * decode(char* inputPath, char* outputPath, struct Node* tree, int size) -
 * takes the file at 'inputPath' and converts the bits back to the corresponding
 * characters from the tree passed in, also takes in the size of the tree to know
 * how many places to skip for the letter frequencies stored in the file
 */
void decode(char* inputPath, char* outputPath, struct Node* tree, int size);

/*
 * freeTree(struct Node* tree) - loops through a node tree and frees every
 * node within its structure and all of the contents of the node
 */
void freeTree(struct Node* tree);

/*
 * freeNodeArray(struct Node* tree) - frees all of the properties of the
 * NodeArray struct tree, and all of the nodes inside of it
 */
void freeNodeArray(struct NodeArray* tree);

/*
 * freeBitArray(char** arr) - loops through a bit array and frees every
 * string within it and the array itself
 */
void freeBitArray(char** arr);


#endif
