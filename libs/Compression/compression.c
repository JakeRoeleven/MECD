/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * 
 * Huffman Compression
 * 
 * Author(s):
 *  Jake Roeleven - 13246638
 * Date Complete:
 *  30/05/2019
 * Notes: 
 *  The follwoing refrences were used to help complete this algorithm:
 *  - https://en.wikipedia.org/wiki/Huffman_coding
 *  - https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
 *  - https://gitlab.com/mehalter/Huffman-Coding-C/blob/master/huffman.c
 *  - https://github.com/DanielScocco/Simple-Huffman-Coding/blob/master/huffman.c
*******************************************************************************/

/*Inclusions*/
#include "compression.h"

/*Testing purposes TODO: Delete*/
int main() {
    Compress();
    Decompress();
    return 0;
}

/*Main function to call compression*/
void Compress() {
    
    char inFileName[1024], outFileName[1024];
    FILE *inFileP, *outFileP;
    long int inFileSize, outFileSize;
    
    printf("Name the file you wish to compress?\n");
    scanf("%s", inFileName);
    
    printf("\nCompressing...");

    inFileP = fopen(inFileName, "rb");
    strcpy(outFileName, inFileName);
    removeFileExtension(outFileName);
    strcat(outFileName, ".min");
    outFileP = fopen(outFileName, "wb");
    
    if(inFileP == NULL) {
        printf("Error! That file does not exist!");   
        exit(1);             
    }

    encodeFile(inFileP, outFileP);

    inFileSize = findFileSize(inFileP);
    outFileSize = findFileSize(outFileP);
    
    printFileStats(inFileSize, outFileSize);
    printf("Your file can now be found at: %s\n\n", outFileName);

    fclose(inFileP);
    fclose(outFileP);

    deleteFile(inFileName);
}

/*Main function to call decompression*/
void Decompress() {

    char inFileName[1024], outFileName[1024];
    FILE *inFileP, *outFileP;
    
    printf("Name the file you wish to decompress?\n");
    scanf("%s", inFileName);

    printf("\nDecompressing...\n");
    
    strcpy(outFileName, inFileName);
    removeFileExtension(outFileName);
    strcat(outFileName, ".txt");

    inFileP = fopen(inFileName, "rb");
    outFileP = fopen(outFileName, "wb");

    if(inFileP == NULL) {
        printf("Error! That file does not exist!");   
        exit(1);             
    }

    decodeFile(inFileP, outFileP);

    printf("Success!\nYour file can be found at: %s\n\n", outFileName);

    fclose(inFileP);
    fclose(outFileP);

    deleteFile(inFileName);
}

/*Build a Huffman Tree and populate it based on the frequencies pased in */
Node *buildHuffmanTree(int frequenciesArray[]) {
    
    int i, length = 0;
    Node *NodelistP[MAX_CHAR_RANGE];
    
    for(i = 0; i < MAX_CHAR_RANGE; i++) {
        if(frequenciesArray[i]) {
            Node *currentNodeP = (Node *)calloc(1, sizeof(Node));
            currentNodeP->contents = i;
            currentNodeP->frequency = frequenciesArray[i];
            NodelistP[length++] = currentNodeP;
        }
    }
    
    while(length > 1) {
        Node *currentNodeP = (Node *)malloc(sizeof(Node));
        qsort(NodelistP, length, sizeof(Node *), compareNodes);

        currentNodeP->leftP = NodelistP[--length];
        currentNodeP->rightP = NodelistP[--length];

        currentNodeP->frequency = currentNodeP->leftP->frequency + 
                                 currentNodeP->rightP->frequency;
        
        NodelistP[length++] = currentNodeP;
    }
    
    return NodelistP[0];
}

/*Build a table to list the nodes to chars*/
char **buildCharacterTable(int frequenciesArray[]) {
    
    static char *tableP[MAX_CHAR_RANGE];
    char *toFindP = (char *)calloc(1, sizeof(char));
    Node* treeP = buildHuffmanTree(frequenciesArray);
    searchHuffmanTree(treeP, tableP, toFindP); 
    freeHuffmanTree(treeP);

    return tableP;
}

/*Recursivly search the huffman tree till we react a node with no neighbours*/
void searchHuffmanTree(Node *treeP, char **tableP, char *toFindP) {
    
    if (!treeP->leftP && !treeP->rightP) tableP[treeP->contents] = toFindP;

    else {
        if(treeP->leftP) {
            searchHuffmanTree(treeP->leftP, tableP, concatSuffix(toFindP, '0'));
        }
        if(treeP->rightP) {
            searchHuffmanTree(treeP->rightP, tableP, concatSuffix(toFindP, '1'));
        } 
        free(toFindP);
    }
}

/*Compare nodes and return a int based on which one is bigger*/
int compareNodes(const void *nodeOneP, const void *nodeTwoP) {
   
    const Node** nodeAPP = (const Node**) nodeOneP;
    const Node** nodeBPP = (const Node**) nodeTwoP;

    if ((*nodeAPP)->frequency == (*nodeBPP)->frequency) return 0;
    else if ((*nodeAPP)->frequency < (*nodeBPP)->frequency) return 1;
    else return -1;
}

/*Write the file header to decode the file*/
void writeFileHeader(FILE *outFileP, int frequenciesArray[]) {
    
    int i, count = 0;
    
    for (i = 0; i < MAX_CHAR_RANGE; i++) {
        if (frequenciesArray[i]) {
            count++;
        }
    }

    fprintf(outFileP, "%d\n", count);

    for (i = 0; i < MAX_CHAR_RANGE; i++) {
        if (frequenciesArray[i]) {
            fprintf(outFileP, "%d %d\n", i, frequenciesArray[i]);
        }
    }
}

/*Read file headers to then decode the file*/
int *readFileHeader(FILE *inFileP) {

    static int frequenciesArray[MAX_CHAR_RANGE];
    int i, count, letter, freq;
    
    if(fscanf(inFileP, "%d", &count) != 1) {
        printf("Invalid input file!");
    }
    
    for(i = 0; i < count; i++) {
        if((fscanf(inFileP, "%d %d", &letter, &freq) != 2) || letter < 0 || letter >= MAX_CHAR_RANGE) {
            printf("invalid input file.");
        }
        
        frequenciesArray[letter] = freq;
    }

    fgetc(inFileP); 
    
    return frequenciesArray;
}

/*Add the encoded bit array to the file*/
void encodeBit(const char *charArrayP, FILE *outFileP) {
    
    static int bit = 0, bitCount = 0;
    
    while(*charArrayP) {

        bit = bit * 2 + *charArrayP - '0';
        bitCount++;
        
        if(bitCount == 8) {
            fputc(bit, outFileP);
            bit = 0;
            bitCount = 0;
        }
        
        charArrayP++;
    }
}

/*Get the encoded bit array from the file*/
int decodeBit(FILE *inFileP) {

    static int bit = 0, bitCount = 0;
    int nextBit;

    if (bitCount == 0) {
        bit = fgetc(inFileP);
        bitCount = (1 << (CHAR_BIT_SIZE - 1));
    }

    nextBit = bit/bitCount;
    bit %= bitCount;
    bitCount /= 2;

    return nextBit;
}

/*Convert the bit array to a readble char*/
int bitToChar(FILE *inFileP, Node *treeP) {

    while (treeP->leftP || treeP->rightP) {
        if(!treeP) {
            printf("Error file format");
            exit(1);;
        }
        else if (decodeBit(inFileP)) {
            treeP = treeP->rightP;
        }
        else {
            treeP = treeP->leftP;
        }
    }
    return treeP->contents;
}

/*Add a digit to the end of a char string and associated memory managment*/
char *concatSuffix(char *currentP, char suffix) {
    char *newChar = (char *)malloc(strlen(currentP) + 2);
    sprintf(newChar, "%s%c", currentP, suffix);
    return newChar;
}

/*Structue processing for encoding a file*/
void encodeFile(FILE *inFileP, FILE *outFileP) {
    
    int c, frequenciesArray[MAX_CHAR_RANGE] = {0};
    char **tablePP;
    
    while((c = fgetc(inFileP)) != EOF) {
        frequenciesArray[c]++;
    } 
    
    frequenciesArray[EOF_FLAG] = 1;
    rewind(inFileP);
    
    tablePP = buildCharacterTable(frequenciesArray);
    writeFileHeader(outFileP, frequenciesArray);
    
    while((c = fgetc(inFileP)) != EOF) {
        encodeBit(tablePP[c], outFileP);
    }
    
    encodeBit(tablePP[EOF_FLAG], outFileP);
    encodeBit("0000000", outFileP);
    
    freeTable(tablePP);
}

/*Structue processing for encoding a file*/
void decodeFile(FILE *inFileP, FILE *outFileP) {
    
    int *frequenciesArray, c;
    Node *treePP;
    
    frequenciesArray = readFileHeader(inFileP);
    treePP = buildHuffmanTree(frequenciesArray);
    
    while((c = bitToChar(inFileP, treePP)) != EOF_FLAG) {
        fputc(c, outFileP);
    }
    
    freeHuffmanTree(treePP);
}

/*Free the allocated memory space of the Huffman tree*/
void freeHuffmanTree(Node *treeP) {
    if (treeP) {
        freeHuffmanTree(treeP->leftP);
        freeHuffmanTree(treeP->rightP);
        free (treeP);
    }
}

/*Free the allocated memory space of the table*/
void freeTable(char *tableP[]) {
    int i;
    for (i = 0; i < MAX_CHAR_RANGE; i++) {
        if (tableP[i]) {
            free(tableP[i]);
        }
    }
}

/*remoce the last four letter of the file*/
char* removeFileExtension(char* fileNameP) {
    size_t nameLength = strlen(fileNameP);
    fileNameP[4 <= nameLength ? nameLength-4 : 0] = '\0';
    return fileNameP;
}

/*Delete the file*/
void deleteFile(char* inFileNameP) {
   remove(inFileNameP);
}

/*Find the file size*/
long int findFileSize(FILE *inFileP) {
    
    fseek(inFileP, 0L, SEEK_END); 
    float fileSize = ftell(inFileP); 
    fclose(inFileP); 
  
    return fileSize; 
}

/*Print the file statistics when compressing*/
void printFileStats(long int inFileSize, long int outFileSize) {
    
    float compressionPercent;
    float byteDiff;

    if (outFileSize >= inFileSize) {
        printf("Error: File is to small to compress!/n");
        exit(0);
    }

    byteDiff = ((float)inFileSize - (float)outFileSize);
    compressionPercent = (byteDiff*100) / (float)inFileSize;

    printf("\nSuccess!\n");
    printf("Your file was compressed from %ld bytes to %ld bytes! \n", inFileSize, outFileSize);
    printf("Approximately %.2f%% compression was achieved!\n", compressionPercent);
}
