/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 * 	Jake Roeleven
 * Date Complete:
*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "compression.h"









void freeNodeArray(NodeArray* tree) {
    //loop through the array of nodes and free each node tree inside of it
    for (int i = 0; i < tree->size; i++)
        freeTree(tree->nodes[i]);
    //free the array of nodes
    free(tree->nodes);
    //free the node array itself
    free(tree);
}

void freeBitArray(char** arr) {
    //loop through the array of string and free each string inside of it
    for(int i = 0; i < 257; i++)
        free(arr[i]);
    //free the array itself
    free(arr);
}

void compressFile(char* inputPath, char* outputPath, char** array) {
    //open the input file for reading
    FILE* rf = fopen(inputPath, "r");
    //open the output file as an append so that we don't overwrite the character frequencies
    //if a file isn't passed in, then we just set the file to NULL
    FILE* wf = outputPath ? fopen(outputPath, "a") : NULL;
    //initialize an empty string to act as the bit buffer
    char* currentBits = malloc(1);
    strcpy(currentBits, "");
    //loop through every character in the file
    for (int ch = fgetc(rf); ch != EOF; ch = fgetc(rf)) {
        //increase the size of the bit buffer to add the new bits
        currentBits = realloc(currentBits, strlen(currentBits) + strlen(array[ch]) + 1);
        //add the new bits to the bit buffer
        strcat(currentBits, array[ch]);
        //if and while the strlen of the bit buffer is greater than 8, we have full characters
        //we can write to the file, and we want to keep the bit buffer as small as we can
        while(strlen(currentBits) >= 8) {
            //we create a temp bit string to hold the first 8 bits in the bit buffer
            char bitString[9];
            //copy the first 8 bits of the bit buffer to the temp bit string
            strncpy(bitString, currentBits, 8);
            //set the terminating character of the bit string
            //remove the first 8 bits from the bit buffer
            memmove(currentBits, currentBits + 8, strlen(currentBits) - 7);
            //if the output file isn't NULL conver the bit string to a base 10 character and
            //write that character to the file
            if (wf) fputc(strtol(bitString, NULL, 2), wf);
            //if the output file is NULL, then we just print the bits to the screen
            else printf("%s", bitString);
        }
    }
    //clase the file since we are done reading it
    fclose(rf);
    //increase the size of our bit buffer to hold the new bits
    currentBits = realloc(currentBits, strlen(currentBits) + strlen(array[256]) + 1);
    //add the new bits to the bit buffer
    strcat(currentBits, array[256]);
    //while the length of the bit buffer isn't divisible by 8
    while(strlen(currentBits) % 8 != 0) {
        //add a 0 to the end of the bit buffer to pad the end with zeros so that it is writable
        //as characters
        currentBits = realloc(currentBits, strlen(currentBits) + 2);
        strcat(currentBits, "0");
    }
    //while the strlen of the bit buffer is 8 or greater write the bits so that we write every bit needed
    while(strlen(currentBits) >= 8) {
        //we create a temp bit string to hold the first 8 bits in the bit buffer
        char bitString[9];
        //copy the first 8 bits of the bit buffer to the temp bit string
        strncpy(bitString, currentBits, 8);
        //remove the first 8 bits from the bit buffer
        memmove(currentBits, currentBits + 8, strlen(currentBits) - 7);
        //if the output file isn't NULL conver the bit string to a base 10 character and
        //write that character to the file
        if (wf) fputc(strtol(bitString, NULL, 2), wf);
        //if the output file is NULL, then we just print the bits to the screen
        else printf("%s", bitString);
    }
    //if the bits are being printed to the screen, add a new line for better viewing
    if(!wf) puts("");
    //free the bit buffer
    free(currentBits);
    //if we are writing to a file, close the file we used for writing
    if (wf) fclose(wf);
}

/*
 * decode(char* inputPath, char* outputPath, Node* tree, int size) -
 * takes the file at 'inputPath' and converts the bits back to the corresponding
 * characters from the tree passed in, also takes in the size of the tree to know
 * how many places to skip for the letter frequencies stored in the file
 */
void decompressFile(char* inputPath, char* outputPath, Node* tree, int size) {
    //open the input file for reading
    FILE* rf = fopen(inputPath, "r");
    //open the output file as an append so that we don't overwrite the character frequencies
    //if a file isn't passed in, then we just set the file to NULL
    FILE* wf = outputPath ? fopen(outputPath, "w") : NULL;
    //set a current node at the top of the tree to help follow the tree down to a character from bits
    Node* currentNode = tree;
    //add a counter to keep track of first few lines to skip the character frequencies stored in the
    //compressed file
    int counter = 0;
    //initialize the previous character to -1
    int prevChar = -1;
    //loop through each character in the input file
    for(int ch = fgetc(rf); ch != EOF; ch = fgetc(rf)) {
        //if the character is ' ', the previous character isn't ' ', and the counter is less than the size + 1,
        //then increase the counter because we are still in the frequency part of the file
        if(ch == ' ' && prevChar != ' ' && counter < size) counter++;
        //once the counter is greater than the size + 1, we are outside of the frequencies portion of the file
        else if(counter >= size)
            //loop through each bit in the current character
            for(int j = 0; j < (8*sizeof(int) + 1); j++) {
                //if the tree is at a base node, then we need to get the current character
                if (!currentNode->left && !currentNode->right) {
                    //if the decompressed character is our pseudo EOF character
                    if(currentNode->contents[0] == 256) {
                        //close reading file
                        fclose(rf);
                        //if we have a writing file, we close that as well
                        if(wf) fclose(wf);
                        //return out of the function
                        return;
                    }
                    //if the character isn't our pseudo EOF character we continue
                    //if we have a output file
                    if(wf)
                        //add the new character to the end of the file
                        fprintf(wf, "%c", currentNode->contents[0]);
                    //if we don't have an output file
                    else
                        //print the character to the screen
                        printf("%c", currentNode->contents[0]);
                    //set the current node to the top of the tree
                    currentNode = tree;
                }
                //loop through the last 8 bits of the integer so that we only get the character bits
                if(j > 23 && j < 32)
                    //set the current node to the left or right depending on if the bit is a 1 or 0 respectively
                    currentNode = (ch << j) & (1 << (8*sizeof(int)-1)) ? currentNode->right : currentNode->left;
            }
        //set the previous character to the what is now the current character
        prevChar = ch;
    }
}

