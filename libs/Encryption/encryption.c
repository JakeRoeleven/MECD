/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * 
 * Encryption
 * 
 * Author(s):
 *  Zinh AL-Sweedy - 12402677
 *  Jake Roeleven - 13246638
 * Date Complete:
 *  4/10/2019
*******************************************************************************/



#include <stdio.h>  /* printf,scanf ,fgets,fread,fwrite,stdin*/
#include <string.h> /* strlen, strcpy,strncpy,strcmp*/
#include <stdlib.h> /* sizeof,NULL */


void encrypt(char *inFileName);
void decrypt(char *inFileName);
void writeToFile(const char *text, char *inFileName);
char* readfromFile(char *inFileName);
void encryptFile();
void decryptFile();

int main(void)  {
    encryptFile();
    decryptFile();
    return 0;
}

void encryptFile() {

    char inFileName[1024];
    printf("Name the file you wish to encrypt: ");
    scanf("%s", inFileName);
    
    FILE *testFile = fopen(inFileName, "r");
    if (testFile == NULL) {
        printf("Error: File not found!\n");
        exit(0);
    }
    fclose(testFile);

    printf("Encrypting...\n");
    encrypt(inFileName);
    printf("Success!\n");

}

void decryptFile() {
    
    char inFileName[1024];
    printf("Name the file you wish to decrypt: ");
    scanf("%s", inFileName);

    FILE *testFile = fopen(inFileName, "r");
    if (testFile == NULL) {
        printf("Error: File not found\n");
        exit(0);
    }
    fclose(testFile);

    printf("Decrypting...\n");
    decrypt(inFileName);
    printf("Success!\n");

}



void encrypt(char *inFileName) {

    int key, i;

    printf("Enter the key: ");
    scanf("%d", &key);
    while (key < 1 || key > 10) {
        printf("Invalid Key! - The key needs to be a positive digit less than 10!\n");
        printf("Enter the key: ");
        scanf("%d", &key);
    }
    
    char *text = readfromFile(inFileName);

    for (i = 0; i < (strlen(text)); i++) {
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
    writeToFile(text, inFileName);
}

void decrypt(char *inFileName) {
    
    int key, i;
    printf("Enter the key: ");
    scanf("%d", &key);
    while (key < 1 || key > 10) {
        printf("Invalid Key! - The key needs to be a positive digit less than 10!\n");
        printf("Enter the key: ");
        scanf("%d", &key);
    }

    char *text = readfromFile(inFileName);

    for (i = 0; i < (strlen(text)); i++) {
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

    writeToFile(text, inFileName); 
}

void writeToFile(const char *text, char *inFileName) {
    
    remove(inFileName);
    FILE *outFileP;
    outFileP = fopen(inFileName,"w");

    int i;
    int len = strlen(text);

    for (i = 0; i < len; i++) {
        fprintf(outFileP, "%c", text[i]);
    }

    fclose(outFileP);
}

char* readfromFile(char *inFileName) {
    
    char *buffer = 0;
    long length;
    FILE * inFileP = fopen(inFileName, "rb");
    if (inFileP == NULL) {
        printf("Error: File not found\n");
        exit(0);
    }

    if (inFileP) {
      fseek (inFileP, 0, SEEK_END);
      length = ftell (inFileP);
      fseek (inFileP, 0, SEEK_SET);
      buffer = malloc (length);
      if (buffer)
      {
        fread (buffer, 1, length, inFileP);
      }
      fclose (inFileP);
    }
    return buffer;
}