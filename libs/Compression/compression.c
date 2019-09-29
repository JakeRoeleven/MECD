/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 * 	Jake Roeleven
 * Date Complete:
*******************************************************************************/

#include "compression.h"

int main() {
    FILE *inFileP, *outFileP;
    inFileP = fopen("text.txt", "rb");
    outFileP = fopen("out.min", "wb");

    encodeFile(inFileP, outFileP);

    fclose(inFileP);
    fclose(outFileP);

    inFileP = fopen("out.min", "rb");
    outFileP = fopen("out.txt", "wb");

    decodeFile(inFileP, outFileP);

    fclose(inFileP);
    fclose(outFileP);

    return 0;
}
/*Build a Huffman Tree and populate it based on the 
  frequencies pased in */
Node *buildHuffmanTree(int frequencies[]) {
    /* Variables */
    int i, len = 0;
    Node *queue[MAX_CHAR];
    
    /* create trees for each character, add to the queue */
    for(i = 0; i < MAX_CHAR; i++)
    {
        if(frequencies[i])
        {
            Node *toadd = (Node *)calloc(1, sizeof(Node));
            toadd->contents = i;
            toadd->frequency = frequencies[i];
            queue[len++] = toadd;
        }
    }
    
    while(len > 1)
    {
        Node *toadd = (Node *)malloc(sizeof(Node));
        
        /* sort - smallest frequency trees are last */
        qsort(queue, len, sizeof(Node *), compareNodes);
        
        /* dequeue two lowest frequency trees, build new tree from them */
        toadd->leftP = queue[--len];
        toadd->rightP = queue[--len];
        toadd->frequency = toadd->leftP->frequency + toadd->rightP->frequency;
        
        queue[len++] = toadd; /* insert back in the queue */
    }
    
    return queue[0];
}

/* TODO Document and Optamize */
int compareNodes(const void *nodeOneP, const void *nodeTwoP) {
   
    const Node** nodeAPP = (const Node**) nodeOneP;
    const Node** nodeBPP = (const Node**) nodeTwoP;

    /*If frequencies are the same*/
    if ((*nodeAPP)->frequency == (*nodeBPP)->frequency) {
        return 0;
    }
    else {
        return ((*nodeAPP)->frequency < (*nodeBPP)->frequency) ? 1 : -1;
    }
}

char **buildCharacterTable( int frequenciesArray[]) {
    static char *tableP[MAX_CHAR];
    char *toFindP = (char *)calloc(1, sizeof(char));
    Node* treeP = buildHuffmanTree(frequenciesArray);
    searchHuffmanTree(treeP, tableP, toFindP); 
    freeHuffmanTree(treeP);

    return tableP;
}

void searchHuffmanTree(Node *treeP, char **tableP, char *toFindP) {
    
    if (!treeP->leftP && !treeP->rightP) {
        tableP[treeP->contents] = toFindP;
    }

    else {
        if(treeP->leftP) {
            searchHuffmanTree(treeP->leftP, tableP, addPrefix(toFindP, '0'));
        }
        if(treeP->rightP) {
            searchHuffmanTree(treeP->rightP, tableP, addPrefix(toFindP, '1'));
        } 
        free(toFindP);
    }
}

char *addPrefix(char *currentP, char prefix) {
    char *newChar = (char *)malloc(strlen(currentP) + 2);
    sprintf(newChar, "%s%c", currentP, prefix);
    return newChar;
}

void writeFileHeader(FILE *outFile, int frequenciesArray[]) {
    
    int i, count = 0;
    
    for (i = 0; i < MAX_CHAR; i++) if (frequenciesArray[i]) count++;
    fprintf(outFile, "%d\n", count);
    for (i = 0; i < MAX_CHAR; i++) {
        if (frequenciesArray[i]) {
            fprintf(outFile, "%d %d\n", i, frequenciesArray[i]);
        }
    }

}

int *readFileHeader(FILE *inFile) {
    
    /*static int frequenciesArray[MAX_CHAR];
    int i, count, current, frequency;

    if (fscanf(inFile, "%d", &count) != 1) {
        printf("Invalid file format!");
        exit(1);;
    }

    for (i = 0; i < count; i++) {
        if(fscanf(inFile, "%d %d", &current, & frequency) != 2) {
            if (current < 0 || current >=MAX_CHAR) {
                printf("Invalid file format");
                exit(1);;
            }
            frequenciesArray[current] = frequency;
        }
    }

    return frequenciesArray;*/
    static int frequencies[MAX_CHAR];
    int i, count, letter, freq;
    
    if(fscanf(inFile, "%d", &count) != 1) printf("invalid input file.");
    
    for(i = 0; i < count; i++)
    {
        if((fscanf(inFile, "%d %d", &letter, &freq) != 2)
           || letter < 0 || letter >= MAX_CHAR) printf("invalid input file.");
        
        frequencies[letter] = freq;
    }
    fgetc(inFile); /* discard last newline */
    
    return frequencies;
}

/*TODO Fix*/
void encodeBit(const char *encoding, FILE *out)
{
    /* buffer holding raw bits and number of bits filled */
    static int bits = 0, bitcount = 0;
    
    while(*encoding)
    {
        /* push bits on from the right */
        bits = bits * 2 + *encoding - '0';
        bitcount++;
        
        /* when we have filled the char, output as a single character */
        if(bitcount == 8)
        {
            fputc(bits, out);
            bits = 0;
            bitcount = 0;
        }
        
        encoding++;
    }
}

int decodeBit(FILE *inFileP) {

    static int bits = 0, bitCount = 0;
    int nextBit;

    if (bitCount == 0) {
        bits = fgetc(inFileP);
        bitCount = (1 << (CHAR_BIT_SIZE - 1));
    }

    nextBit = bits / bitCount;
    bits %= bitCount;
    bitCount /= 2;

    return nextBit;

}

int bitToChar(FILE *inFileP, Node *treeP) {
    while (treeP->leftP || treeP->rightP) {
        if (decodeBit(inFileP)) {
            treeP = treeP->rightP;
        }
        else {
            treeP = treeP->leftP;
        }
        if(!treeP) {
            printf("Error file format");
            exit(1);;
        }
    }
    return treeP->contents;
}

void freeHuffmanTree(Node *treeP) {
    if (treeP) {
        freeHuffmanTree(treeP->leftP);
        freeHuffmanTree(treeP->rightP);
        free (treeP);
    }
}

void freeTable(char *tableP[]) {
    int i;
    for (i = 0; i < MAX_CHAR; i++) {
        if (tableP[i]) {
            free(tableP[i]);
        }
    }
}

void encodeFile(FILE *in, FILE *out) {
    int c, frequencies[MAX_CHAR] = {0};
    char **table;
    
    while((c = fgetc(in)) != EOF) frequencies[c]++;
    
    frequencies[EOF_FLAG] = 1;
    rewind(in);
    
    table = buildCharacterTable(frequencies);
    writeFileHeader(out, frequencies);
    
    while((c = fgetc(in)) != EOF)
        encodeBit(table[c], out);
    
    /* use FAKE_EOF to indicate end of input */
    encodeBit(table[EOF_FLAG], out);
    
    /* write an extra 8 blank bits to flush the output buffer */
    encodeBit("0000000", out);
    
    freeTable(table);
}

/*TODO Document*/
void decodeFile(FILE *in, FILE *out) {
    int *frequencies, c;
    Node *tree;
    
    frequencies = readFileHeader(in);
    tree = buildHuffmanTree(frequencies);
    
    while((c = bitToChar(in, tree)) != EOF_FLAG) {
        fputc(c, out);
    }
    
    freeHuffmanTree(tree);
}

 

