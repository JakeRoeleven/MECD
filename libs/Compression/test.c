#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "compression.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void) {
    compressFile();
    return 0;
}

/* For the creation of the node strucutres within our huffman tree*/
Node* createNode(int *nodeContentP, int nodeSize, int nodeFreq, Node* leftP, Node* rightP) {

    int i;
    Node *newNodeP = malloc(sizeof(Node));
    int *nodeContentsP = malloc(sizeof(int) *nodeSize);
   
    for(i = 0; i < nodeSize; i++) {
        nodeContentsP[i] = nodeContentP[i]; 
    }

    newNodeP->contents = nodeContentsP;
    newNodeP->size = nodeSize;
    newNodeP->freq = nodeFreq;
    newNodeP->left = leftP;
    newNodeP->right = rightP;

    return newNodeP;
}

/*Create a base node*/
Node* createBaseNode(int *nodeContentsP, int nodeFreq) {
    return createNode(nodeContentsP, 1, nodeFreq, NULL, NULL);
}

/*A recursive function to build the huffman Tree out of Nodes*/
Node* buildTree(Tree* list) {

    int i;
    /*while (treeListP->size > 1) {
        int* smallestNodes = getSmallest(treeListP);
        int newInts[treeListP->nodes[smallestNodes[1]]->size + treeListP->nodes[smallestNodes[0]]->size];

        for(i = 0; i < treeListP->nodes[smallestNodes[1]]->size; i++) {
            newInts[place++] = treeListP->nodes[smallestNodes[1]]->contents[i];
        }
        for(i = 0; i < treeListP->nodes[smallestNodes[0]]->size; i++) {
            newInts[place++] = treeListP->nodes[smallestNodes[0]]->contents[i];
        }

        treeListP->nodes[smallestNodes[1]] = createNode(newInts, treeListP->nodes[smallestNodes[1]]->size + treeListP->nodes[smallestNodes[0]]->size, 
            treeListP->nodes[smallestNodes[1]]->freq + treeListP->nodes[smallestNodes[0]]->freq, 
            treeListP->nodes[smallestNodes[1]], treeListP->nodes[smallestNodes[0]]);
        
        memmove(treeListP->nodes + smallestNodes[0], treeListP->nodes + smallestNodes[0] + 1, 
            (treeListP->size - smallestNodes[0] - 1) * sizeof(Node*));
        treeListP->size--;


        return buildTree(treeListP);
        }
    return treeListP->nodes[0];*/

    while (list->size > 1) {

        int* smallest = getSmallest(list);;
        int one = &smallest[1];
        int zero = &smallest[0];
        int newInts[list->nodes[one]->size + list->nodes[zero]->size];

        int place = 0;

        for(i = 0; i < list->nodes[one]->size; i++) {
            newInts[place++] = list->nodes[one]->contents[i];
        }
        for (i = 0; i < list->nodes[zero]->size; i++) {
            newInts[place++] = list->nodes[zero]->contents[i];
        }
        list->nodes[one] = createNode(newInts, list->nodes[one]->size + list->nodes[zero]->size, 
            list->nodes[one]->freq + list->nodes[zero]->freq, 
            list->nodes[one], list->nodes[zero]);
        memmove(list->nodes + zero, list->nodes + zero + 1, (list->size - zero - 1) * sizeof(Node*));
        list->size--;


        return buildTree(list);
        }
    return list->nodes[0];

    /*    int* smallest = getSmallest(list);
        printf("%d", &smallest[1]);
        int one = &smallest[1];
        int zero = &smallest[0];
        int newInts[list->nodes[one]->size + list->nodes[zero]->size];
        int place = 0;
        for(i = 0; i < list->nodes[one]->size; i++) {
            newInts[place++] = list->nodes[one]->contents[i];
        }
        for (i = 0; i < list->nodes[zero]->size; i++) {
            newInts[place++] = list->nodes[zero]->contents[i];
        }
        list->nodes[one] = createNode(newInts, list->nodes[one]->size + list->nodes[zero]->size, 
            list->nodes[one]->freq + list->nodes[zero]->freq, 
            list->nodes[one], list->nodes[zero]);
        memmove(list->nodes + zero, list->nodes + zero + 1, (list->size - zero - 1) * sizeof(Node*));
        list->size--;
    return list->nodes[zero];*/
}


/*Construct an array of the Ascii Bit codes*/
char** generateBitAsciiArray(Node* treeP) {
    
    int i;
    char** bitArray = malloc(sizeof(char*) * 257);

    for(i = 0; i < 257; i++) {
        bitArray[i] = getCode(treeP, i, NULL);
    }

    return bitArray;
}

/*Find the corresponding bitCode for the Ascii char*/
char* getCode(Node* nextP, int find, char* bitsP) {

    int found, i;
    char* newCharP;
    /*Check that both the left and right nodes are not NULL/Empty*/
    if (nextP->left && nextP->right) {

        /* Allocate memory space for the bits array as part of the recursive function*/
        if (bitsP == NULL) {
            bitsP = malloc(1);
            strcpy(bitsP, "");
        }

        /*Check to see if we have found the char we are looking for*/
        found = 0;
        for(i = 0; i < nextP->left->size; ++i) {
            if(nextP->left->contents[i] == find) {
                found = 1;
            }
        }

        /*Choose which node to view next*/
        newCharP = found ? "0" : "1";
        nextP = strcmp(newCharP, "0") == 0 ? nextP->left : nextP->right;

        /*Resize the bit string and add the new bit to the end of the string*/
        bitsP = realloc(bitsP, strlen(bitsP) + 2);
        strcat(bitsP, newCharP);

        /*Recursivly call the function till we reach a base node*/
        return getCode(nextP, find, bitsP);
    }

    return bitsP;
}

/* Find the smallest frequency of two nodes*/
int* getSmallest(Tree* treeP) {

    int smallestNode[2];
    int i;

    for (i = 0; i < treeP->size; i++)
        if (treeP->nodes[i]->freq <= treeP->nodes[smallestNode[0]]->freq) {
            smallestNode[1] = smallestNode[0];
            smallestNode[0] = i;
        }

    if (smallestNode[1] == smallestNode[0]) {
        smallestNode[1] = smallestNode[0] == 0 ? 1 : 0;
        for(i = 0; i < treeP->size; i++)
            if (i != smallestNode[0] && treeP->nodes[i]->freq < treeP->nodes[smallestNode[1]]->freq) {
                smallestNode[1] = i;
            }
    }

    return smallestNode;
}

/*Create a Tree of the frequency of chars of a read in file*/
Tree* readFrequencyFile(char* filePathP) {

    FILE* fp = fopen(filePathP, "r");

    int* list = calloc(257, sizeof(int));
    int ch, place = 0, size = 0;
    char* charBuffer = malloc(1);
    strcpy(charBuffer, "");
    int prevPrevChar = -1, prevChar = -1, newChar = -1;

    /*Loop through ever character in the file*/
    for(ch = fgetc(fp); ch != EOF; ch = fgetc(fp)) {

        /*If the place is 0 and the character is ' ' then we are at the end*/
        if(place == 0 && ch == ' ') {
            /*TODO: FIx This*/
            /*size = atoi(charBuffer);*/
            size = atoi(charBuffer);

            free(charBuffer);
            charBuffer = malloc(1);
            strcpy(charBuffer, "");

            place++;
        }
        /*if the place is greater than the size, then all reable Ascii chars have been read*/
        else if(place > size) break;
        /* Deal with spaces after numbers*/
        else if (ch == ' ' && prevChar != ' ') {
            /*TODO: Fix This*/
            /*size = atoi(charBuffer);*/
            list[newChar] = atoi(charBuffer);
            place++;

            free(charBuffer);
            charBuffer = malloc(1);
            strcpy(charBuffer, "");
        } 
        /*Deal with chars after numbers*/
        else if(prevChar == ' ' && prevPrevChar != ' ') {
            newChar = ch;
        } 
        /*Deal with numbers by adding them to the end of the Char Buffer*/
        else {
            /*Resize Char Buffer*/
            charBuffer = realloc(charBuffer, strlen(charBuffer) + 2);
            strcat(charBuffer, (char*) &ch);
        }
        prevPrevChar = prevChar;
        prevChar = ch;
    }

    fclose(fp);
    free(charBuffer);

    /* 1 is used to signal end of file */
    list[256] = 1;
    size++;

    /*Create an Tree from the list*/
    Tree* freqTreeP = arrayFromList(list, size);

    free(list);

    return freqTreeP;
}

Tree* buildFrequencyFile(char* filePathP, char* outputPathP){
    
    FILE* fp = fopen(filePathP, "r");

    int* list = calloc(257, sizeof(int));
    int size = 0, ch, i;

    /*Loop through each character in the file*/
    for(ch = fgetc(fp); ch != EOF; ch = fgetc(fp)) {
        
        if (list[ch] == 0) {
            size++;
        }

        list[ch]++;
    }
    fclose(fp);

    /*Use 1 as end of File indicator*/
    list[256] = 1;
    size++;

    /*Convert the list of frequencies to an tree*/
    Tree* freqTreeP = arrayFromList(list, size);

    /*check if an output file was specified for writing to*/
    if(outputPathP) {
        /*Write to this file*/
        FILE* op = fopen(outputPathP, "w");
    
        fprintf(op, "%d ", size - 1);
        for(i = 0; i < 256; i++)
            /*if the frequency isn't 0, store the character and its frequency in the file*/
            if(list[i] != 0) fprintf(op, "%c%d ", i, list[i]);
        fclose(op);
    }

    free(list);
    return freqTreeP;
}

Tree* arrayFromList(int* listP, int size) {
     
    Tree* freq = malloc(sizeof(Tree));
    freq->nodes = malloc(sizeof(Node) * size);
    int place = 0, i;

    for(i = 0; i < 257; i++)
        if(listP[i] != 0) {
            freq->nodes[place++] = createBaseNode((int*) &i, listP[i]);
        }
    freq->size = size;
    return freq;
}

void freeTree(Node* treeP) {
    /*Free non base nodes*/
    if (treeP->left && treeP->right) {
        freeTree(treeP->left);
        freeTree(treeP->right);
        free(treeP->contents);
        free(treeP);
    /*Free base nodes*/
    } 
    else {
        free(treeP->contents);
        free(treeP);
    }
}

void freeNodeArray(Tree* treeP) {

    int i;
    for (i = 0; i < treeP->size; i++) {
        freeTree(treeP->nodes[i]);
    }
    free(treeP->nodes);
    free(treeP);
}

void freeBitArray(char** arrP) {

    int i;
    for(i = 0; i < 257; i++) {
        free(arrP[i]);
    }
    free(arrP);
}

/*TODO Document*/
void compression(char* inputPath, char* outputPath, char** array) {

    int ch;
    /* TODO: Fix Teneray Operator */
    FILE* rf = fopen(inputPath, "r");
    FILE* wf = outputPath ? fopen(outputPath, "a") : NULL;

    /*Initialize an empty string to act as the bit buffer*/
    char* currentBits = malloc(1);
    strcpy(currentBits, "");
    /*Loop through every character in the file*/
    for (ch = fgetc(rf); ch != EOF; ch = fgetc(rf)) {

        currentBits = realloc(currentBits, strlen(currentBits) + strlen(array[ch]) + 1);
        strcat(currentBits, array[ch]);
        while(strlen(currentBits) >= 8) {
            char bitString[9];
            strncpy(bitString, currentBits, 8);
            memmove(currentBits, currentBits + 8, strlen(currentBits) - 7);
            if (wf) {
                fputc(strtol(bitString, NULL, 2), wf);
            }
            else printf("%s", bitString);
        }
    }

    fclose(rf);
    currentBits = realloc(currentBits, strlen(currentBits) + strlen(array[256]) + 1);
    strcat(currentBits, array[256]);
    while(strlen(currentBits) % 8 != 0) {
        currentBits = realloc(currentBits, strlen(currentBits) + 2);
        strcat(currentBits, "0");
    }
   
    while(strlen(currentBits) >= 8) {
        char bitString[9];
        strncpy(bitString, currentBits, 8);
        memmove(currentBits, currentBits + 8, strlen(currentBits) - 7);
        if (wf) fputc(strtol(bitString, NULL, 2), wf);
        else printf("%s", bitString);
    }

    if(!wf) puts("");
    free(currentBits);
    if (wf) fclose(wf);
}

void compressFile(void) {

    char* inFilePath = "in.txt";
    char* outFilePath = "out.min";
    Tree* x;
    Node* top;

    printf("Lets Compress\n");
    printf("%s\n", inFilePath);
    x = buildFrequencyFile(inFilePath, outFilePath);
    top = buildTree(x);
    char** array = generateBitAsciiArray(top);
    compression(inFilePath, outFilePath, array);
    freeBitArray(array);
    freeNodeArray(x);


}