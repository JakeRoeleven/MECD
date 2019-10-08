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

#ifndef ENCRYPTION
#define ENCRYPTION


#include <stdio.h>  /* printf,scanf ,fgets,fread,fwrite,stdin*/
#include <string.h> /* strlen, strcpy,strncpy,strcmp*/
#include <stdlib.h> /* sizeof,NULL */


void encrypt(char *inFileName);
void decrypt(char *inFileName);
void writeToFile(const char *text, char *inFileName);
char* readfromFile(char *inFileName);
void encryptFile();
void decryptFile();

#endif
