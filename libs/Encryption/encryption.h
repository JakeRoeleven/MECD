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

/*Double Inclusion Guards*/
#ifndef ENCRYPTION
#define ENCRYPTION

/*Inclusions*/
#include <stdio.h>  /* printf,scanf ,fgets,fread,fwrite,stdin*/
#include <string.h> /* strlen, strcpy,strncpy,strcmp*/
#include <stdlib.h> /* sizeof,NULL */

/*Function Prototypes*/
void encrypt(char *inFileName);
void decrypt(char *inFileName);
void writeToFile(const char *text, char *inFileName);
char* readfromFile(char *inFileName);
void encryptFile();
void decryptFile();

#endif
