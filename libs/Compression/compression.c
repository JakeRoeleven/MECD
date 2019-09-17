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

Node* createNode(int *nodeContentsp, int nodeSize, int nodeFreq, Node *leftp, Node *rightp) {

    int i;
    Node *newNodeP = malloc(sizeof(struct Node));
    int *nodeContentsp = malloc(sizeof(int) *size);
   
    for(i = 0; i < arrsize; i++) {
        inputInts[i] = ints[i]; 
    }

    newNodeP->contents = nodeContentsp;
    newNodeP->size = nodeSize;
    newNodeP->freq = nodeFreq;
    newNodeP->left = leftp;
    newNodeP->right = rightp;

    return newNodeP;
}

Node* createBaseNode(int *nodeContentsp, int nodeFreq) {
	return createNode(nodeContentsp, 1, nodeFreq, NULL, NULL);
}
