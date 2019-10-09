/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * 
 * Encryption - Substutition Shift Cypher
 * 
 * Author(s):
 *  Zinh AL-Sweedy - 12402677
 *  Jake Roeleven - 13246638
 * Date Complete:
 *  4/10/2019
 * Refrences:
 *  https://codescracker.com/c/program/c-program-encrypt-file.htm
 *  https://medium.com/@randerson112358/programming-encryption-algorithms-
 *  520cb98c039d
 *  https://docs.microsoft.com/en- us/windows/win32/seccrypto/example-c-program-
 *  using-cryptencryptmessage- and-cryptdecryptmessage
 *  https://c-program-example.com/2012/04/c-program-to-encrypt-and-decrypt-a-
 *  password.html>  
*******************************************************************************/

/*Inclusions*/
#include "encryption.h"

/* Debugging     
int main(void)  {
    encryptFile();
    decryptFile();
    return 0;
}*/

/* Process to encrypt the file and related Error Checks */
void encryptFile(char *inFileNamePP) {
    
    FILE *fileP = fopen(inFileNamePP, "r");
    if (fileP == NULL) {
        printf("Error: File not found!\n\n");
        exit(0);
    }
    fclose(fileP);

    printf("Encrypting...\n");
    encrypt(inFileNamePP);
    printf("Success! File Encrypted!\n");

}

/* Process to decrypt the file and related Error Checks */
void decryptFile(char *inFileNamePP) {

    FILE *fileP = fopen(inFileNamePP, "r");
    if (fileP == NULL) {
        printf("Error: File not found\n\n");
        exit(0);
    }
    fclose(fileP);

    printf("Decrypting...\n");
    decrypt(inFileNamePP);
    printf("Success! File Decrypted\n");

}

/* Substiution Shift Cypher Algorithm */
void encrypt(char *inFileNameP) {

    int key, i;

    printf("Warning if you forget your key you will not be able ");
    printf("to decyrpt your file!");
    printf("\nEnter the key: ");
    scanf("%d", &key);
    while (key < 1 || key > 10) {
        printf("Invalid Key! - The key needs to be a positive digit" 
               " less than 10!\n");
        printf("Enter the key: ");
        scanf("%d", &key);
    }
    
    char *textP = readfromFile(inFileNameP);

    /*Shifts*/
    for (i = 0; i < (strlen(textP)); i++) {
        if (textP[i] >= 'a' && textP[i] <= 'z')
        {
            textP[i] = (textP[i] - 'a' - key + 26) % 26 + 'a';
        }
        else if (textP[i] >= 'A' && textP[i] <= 'Z')
        {
           textP[i] = (textP[i] - 'A' - key + 26) % 26 + 'A';
        }
        else if (textP[i] >= '0' && textP[i] <= '9')
        {
            textP[i] = ((textP[i] - '0' - key)%10 + 10)%10 + '0';
        }
    }

    writeToFile(textP, inFileNameP);
}

/* Substiution Shift Cypher Algorithm */
void decrypt(char *inFileNameP) {
    
    int key, i;

    printf("Warning if you enter the wrong key your file will be corrupted");
    printf("\nEnter the key: ");;
    scanf("%d", &key);
    while (key < 1 || key > 10) {
        printf("Invalid Key! - The key needs to be a positive digit "
               " less than 10!\n");
        printf("Enter the key: ");
        scanf("%d", &key);
    }

    char *textP = readfromFile(inFileNameP);

    /* Shifts */
    for (i = 0; i < (strlen(textP)); i++) {
        if (textP[i] == ' ')
        {
             textP[i] = textP[i];
        }
        else if (textP[i] >= 'a' && textP[i] <= 'z')
        {
             textP[i] = (textP[i] - 'a' + key + 26) % 26 + 'a';
        }
        else if (textP[i] >= 'A' && textP[i] <= 'Z')
        {
           textP[i] = (textP[i] - 'A' + key + 26) % 26 + 'A';

        }
        else if (textP[i] >= '0' && textP[i] <= '9')
        {
            textP[i] = (textP[i] - '0' + key)%10 + '0';
        }
    }

    writeToFile(textP, inFileNameP); 
}

/* Write the string to a file */
void writeToFile(const char *textP, char *inFileNameP) {
    
    remove(inFileNameP);
    FILE *outFileP;
    outFileP = fopen(inFileNameP, "w");

    int i;
    int len = strlen(textP);

    for (i = 0; i < len; i++) {
        fprintf(outFileP, "%c", textP[i]);
    }

    fclose(outFileP);
}

/*Open the file and reas its contents to a dynamic sized string*/
char* readfromFile(char *inFileNameP) {
    
    char *fileBufferP = 0;
    unsigned length;
    FILE * inFileP = fopen(inFileNameP, "rb");
    
    if (inFileP == NULL) {
        printf("Error: File not found!\n\n");
        exit(0);
    }

    if (inFileP) {
      fseek (inFileP, 0, SEEK_END);
      length = ftell(inFileP);
      fseek (inFileP, 0, SEEK_SET);
      fileBufferP = malloc(length);
      
      if (fileBufferP) {
        fread (fileBufferP, 1, length, inFileP);
      }

      fclose (inFileP);
    }

    return fileBufferP;  
}
