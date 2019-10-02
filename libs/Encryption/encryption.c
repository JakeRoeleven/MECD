#include <stdio.h>  /* printf,scanf ,fgets,fread,fwrite,stdin*/
#include <string.h> /* strlen, strcpy,strncpy,strcmp*/
#include <stdlib.h> /* sizeof,NULL */

/******************************************************************************
 * List preprocessing directives - you may define your own.
******************************************************************************/
/* #define 
 */
/******************************************************************************
 * List structs - definition for struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
******************************************************************************/

/*********************************************************************************
 * Function prototypes - all the prototypes for the functions used in the program
**********************************************************************************/
void encrypt(FILE *inFileP, char *outFile);
void decrypt(FILE *inFileP, char *outFile);
unsigned int findFileSize(FILE * inFile);
void writeStringToFile(char *text, char *outFile, FILE *inFile);
void encryptFile();
void decryptFile();

/* search for func to change the file to plain text to pass it to cipher method */
/******************************************************************************
 * Main: is the main function in the program:
 * in the main function, the program read the choice from the user to know what 
 * is asked for and deal with each choice from the user in the correct way.
 * inputs:
 * - none
 * outputs:
 * - 0 when it finished dealing with the program.
******************************************************************************/
int main(void)
{
    encryptFile();
    decryptFile();

    return 0;
}

void encryptFile() {

    char inFileName[1024];
    FILE *inFileP;

    printf("Name the file you wish to encrypt: ");
    scanf("%s", inFileName);
    inFileP = fopen(inFileName, "rb");
    if (inFileP == NULL) {
        printf("Error: File not found");
    }

    printf("Encrypting...\n");
    encrypt(inFileP, inFileName);
    printf("Success!\n");
}

void decryptFile() {
    char inFileName[1024];
    FILE *inFileP;

    printf("Name the file you wish to decrypt: ");
    scanf("%s", inFileName);
    inFileP = fopen(inFileName, "rb");
    if (inFileP == NULL) {
        printf("Error: File not found");
    }

    printf("Decrypting...\n");
    decrypt(inFileP, inFileName);
    printf("Success!\n");
}



void encrypt(FILE *inFile, char *outFile) {

    int key;
    int i, j, c;
    char text[findFileSize(inFile)];

    printf("Enter the key: ");
    scanf("%d", &key);
    while (key < 1 || key > 10) {
        printf("Invalid Key! - The key needs to be a positive digit less than 10!\n");
        printf("Enter the key: ");
        scanf("%d", &key);
    }
    
    j = 0;
    while ((c = fgetc(inFile)) != EOF) {
        text[j] = c;
        j++;
    }
    
    for (i = 0; i < j; i++)
    {
         if (text[i] >= 'a' && text[i] <= 'z')
        {
            text[i] = (text[i] - 'a' - key + 26) % 26 + 'a';
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
           text[i] = (text[i] - 'A' - key + 26) % 26 + 'A';
        }
        else if (text[i] >= '0' && text[i] <= '9')
        {
            text[i] = ((text[i] - '0' - key)%10 + 10)%10 + '0';
        }
    }
    writeStringToFile(text, outFile, inFile);
}

void decrypt(FILE *inFile, char *outFile)
{
    int i, key, c, j = 0;
    printf("Enter the key: ");
    scanf("%d", &key);
    while (key < 1 || key > 10) {
        printf("Invalid Key! - The key needs to be a positive digit less than 10!\n");
        printf("Enter the key: ");
        scanf("%d", &key);
    }

    unsigned int fileSize = findFileSize(inFile);
    char text[fileSize];
    
    while ((c = fgetc(inFile)) != EOF) {
        text[j] = c;
        j++;
    }

    for (i = 0; i < j; i++)
    {
        if (text[i] == ' ')
        {
             text[i] = text[i];
        }
        else if (text[i] >= 'a' && text[i] <= 'z')
        {
             text[i] = (text[i] - 'a' + key + 26) % 26 + 'a';
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
           text[i] = (text[i] - 'A' + key + 26) % 26 + 'A';

        }
        else if (text[i] >= '0' && text[i] <= '9')
        {
            text[i] = (text[i] - '0' + key)%10 + '0';
        }
    }
    writeStringToFile(text, outFile, inFile); 
}

unsigned int findFileSize(FILE * inFile) {
    unsigned int i = 0;
    int c;
    while ((c = fgetc(inFile)) != EOF) {
        i++;
    }
    rewind(inFile);
    return i;
}

void writeStringToFile(char *text, char *fileNameP, FILE *inFileP) {
    fclose(inFileP);
    remove(fileNameP);
    FILE *outFileP;
    outFileP = fopen(fileNameP,"w");
    fprintf(outFileP, "%s\n", text);
    fclose(outFileP);
}
