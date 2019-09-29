#include "compression.h"

/* compare two Huffman trees based on frequency, descending order */
int CmpTrees(const void *a, const void *b)
{
    const htree **x = (const htree **) a, **y = (const htree **) b;
    if((*x)->freq == (*y)->freq) return 0;
    else return ((*x)->freq < (*y)->freq) ? 1 : -1;
}

/* create a new string with given letter concatenated on to the prefix */
char *Concat(char *prefix, char letter)
{
    char *result = (char *)malloc(strlen(prefix) + 2);
    sprintf(result, "%s%c", prefix, letter);
    return result;
}

/* print specified error message and quite */
void Error(const char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

/* build and return a Huffman tree based on a frequency table */
htree *BuildTree(int frequencies[])
{
    int i, len = 0;
    htree *queue[CHAR_RANGE];
    
    /* create trees for each character, add to the queue */
    for(i = 0; i < CHAR_RANGE; i++)
    {
        if(frequencies[i])
        {
            htree *toadd = (htree *)calloc(1, sizeof(htree));
            toadd->letter = i;
            toadd->freq = frequencies[i];

            queue[len++] = toadd;
        }
    }
    
    while(len > 1)
    {
        htree *toadd = (htree *)malloc(sizeof(htree));
        
        /* sort - smallest frequency trees are last */
        qsort(queue, len, sizeof(htree *), CmpTrees);
        
        /* dequeue two lowest frequency trees, build new tree from them */
        toadd->left = queue[--len];
        toadd->right = queue[--len];
        toadd->freq = toadd->left->freq + toadd->right->freq;
        
        queue[len++] = toadd; /* insert back in the queue */
    }
    
    return queue[0]; /* last tree in the queue is the full Huffman tree */
}

/* deallocate given Huffman tree */
void FreeTree(htree *tree)
{
    if(tree)
    {
        FreeTree(tree->left);
        FreeTree(tree->right);
        free(tree);
    }
}

/* traverse the Huffman tree to build up a table of encodings */
void TraverseTree(htree *tree, char **table, char *prefix)
{
    if(!tree->left && !tree->right) table[tree->letter] = prefix;
    else
    {
        if(tree->left) TraverseTree(tree->left, table, Concat(prefix, '0'));
        if(tree-> right) TraverseTree(tree->right, table, Concat(prefix, '1'));
        free(prefix);
    }
}

/* build a table of Huffman encodings given a set of frequencies */
char **BuildTable(int frequenciesArray[])
{
    static char *tableP[CHAR_RANGE];
    char *toFindP = (char *)calloc(1, sizeof(char));
    htree* treeP = BuildTree(frequenciesArray);
    TraverseTree(treeP, tableP, toFindP); 
    FreeTree(treeP);

    return tableP;
}

/* deallocate table of Huffman encodings */
void FreeTable(char *table[])
{
    int i;
    for(i = 0; i < CHAR_RANGE; i++) if(table[i]) free(table[i]);
}

/* output the Huffman header for an encoded file */
void WriteHeader(FILE *outFile, int frequenciesArray[])
{
    
    int i, count = 0;
    
    for (i = 0; i < CHAR_RANGE; i++) if (frequenciesArray[i]) count++;
    fprintf(outFile, "%d\n", count);
    for (i = 0; i < CHAR_RA; i++) {
        if (frequenciesArray[i]) {
            fprintf(outFile, "%d %d\n", i, frequenciesArray[i]);
        }
    }
}

/* read in the header of a Huffman encoded file */
int *ReadHeader(FILE *in)
{
    static int frequencies[CHAR_RANGE];
    int i, count, letter, freq;
    
    if(fscanf(in, "%d", &count) != 1) Error("invalid input file.");
    
    for(i = 0; i < count; i++)
    {
        if((fscanf(in, "%d %d", &letter, &freq) != 2)
           || letter < 0 || letter >= CHAR_RANGE) Error("invalid input file.");
        
        frequencies[letter] = freq;
    }
    fgetc(in); /* discard last newline */
    
    return frequencies;
}

/* write the given bit encoding to the output file */
void WriteBits(const char *encoding, FILE *out)
{
    /* buffer holding raw bits and number of bits filled */
    static int bits = 0, bitcount = 0;
    
    while(*encoding)
    {
        /* push bits on from the right */
        bits = bits * 2 + *encoding - '0';
        bitcount++;
        
        /* when we have filled the char, output as a single character */
        if(bitcount == CHAR_BITS)
        {
            fputc(bits, out);
            bits = 0;
            bitcount = 0;
        }
        
        encoding++;
    }
}

/* read a single bit from the input file */
int ReadBit(FILE *in)
{
    /* buffer holding raw bits and size of MSB filled */
    static int bits = 0, bitcount = 0;
    int nextbit;
    
    if(bitcount == 0)
    {
        bits = fgetc(in);
        bitcount = (1 << (CHAR_BITS - 1));
    }
    
    nextbit = bits / bitcount;
    bits %= bitcount;
    bitcount /= 2;
    
    return nextbit;
}

/* decode and return a single character from the input using the given Huffman
 * tree */
int DecodeChar(FILE *in, htree *tree)
{
    while(tree->left || tree->right)
    {
        if(ReadBit(in)) tree = tree->right;
        else tree = tree->left;
        
        if(!tree) Error("invalid input file.");
    }
    return tree->letter;
}

/* decode the Huffman-encoded file in and save the results to out */
void Decode(FILE *in, FILE *out)
{
    int *frequencies, c;
    htree *tree;
    
    frequencies = ReadHeader(in);
    tree = BuildTree(frequencies);
    
    while((c = DecodeChar(in, tree)) != FAKE_EOF)
        fputc(c, out);
    
    FreeTree(tree);
}

/* create a Huffman encoding for the file in and save the encoded version to
 * out */
void Encode(FILE *in, FILE *out)
{
    int c, frequencies[CHAR_RANGE] = { 0 };
    char **table;
    
    while((c = fgetc(in)) != EOF) frequencies[c]++;
    
    frequencies[FAKE_EOF] = 1;
    rewind(in);
    
    table = BuildTable(frequencies);
    WriteHeader(out, frequencies);
    
    while((c = fgetc(in)) != EOF)
        WriteBits(table[c], out);
    
    /* use FAKE_EOF to indicate end of input */
    WriteBits(table[FAKE_EOF], out);
    
    /* write an extra 8 blank bits to flush the output buffer */
    WriteBits("0000000", out);
    
    FreeTable(table);
}

int main()
{
    FILE *in, *out;

    in = fopen("text.txt", "rb");
    out = fopen("out.min", "wb");
    
    Encode(in, out);
    
    fclose(in);
    fclose(out);
    
    return 0;
}