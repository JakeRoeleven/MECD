/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 *  Jake Roeleven - 13246638
 *  Thomas Coates - 13276922
 *  Beichen Man   - 12416780
 *  Zinh AL-Sweedy - 12402677
 * Date Complete:
 *  8/10/2019
*******************************************************************************/

/*Double Inclusion Guard*/
#ifndef MAIN
#define MAIN

/*Inclusions*/
#include <stdio.h>  /* printf,scanf ,fgets,fread,fwrite,stdin*/
#include <string.h> /* strlen, strcpy,strncpy,strcmp*/
#include <stdlib.h> /* sizeof,NULL */
#include "libs/Interface/interface.h"

/*Green Text Defined Here*/
#define Green "\e[32m"
#define printf(X) printf(Green "%s",X);

/*Function Prototypes*/
void utilityMenu();
void helpMenu();

/* Main Function
Takes in the command line arguments
Calls function from interface.h */
int main(int argc, char *argv[]) {
    
    int i;

    printf("\n\n");

    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            switch(*argv[i]) {  
                case 'h': 
                    helpMenu();
                    break;
                case 'c': 
                    createRecords();
                    break;
                case 'v': 
                    displayRecords();
                    break;
                case 'e': 
                    encryptAndCompressFile();
                    break;
                case 'd': 
                    decryptAndDecompressFile();
                    break;
                case 'u': 
                    utilityMenu();
                    break;
                case 'r': 
                    viewFileDatabase();
                    break;
                default:
                    printf("Sorry, that's not a valid argument!\n");
                    printf("The following arguments are available: \n"
                           "---------------------------------------------------"
                           "--------------\n"
                           "h - View the Help Menu\n"
                           "c - Create and Save Military Records\n"
                           "v - View Military Records\n"
                           "e - Encrypt and Compress Records\n"
                           "d - Decompress and Decrypt Records\n"
                           "u - View the Utility Menu (access the Help Menu for" 
                           " more info...)\n"
                           "r - View Recent Files\n"
                           "---------------------------------------------------"
                           "--------------\n\n");
                    return 0;
            } 
        }
    } 
    else {
        printf("Hey! You didn't pass in an argument!\nTry Again!"
               " Enter argument h for help.\n\n");
        return 0;
    }

    printf("\n\n");
    
    /*Saftey Return*/
    return 0;
}

/*Prints the help menu*/
void helpMenu() {
    
    printf("Welcome to the MECD Help Menu!\n\n");
    printf("The following arguments are available to be passed in: \n"
           "-----------------------------------------------------------------\n"
           " h - View this Help Menu\n"
           " c - Create and Save Military Records\n"
           "     > This option allows you to create new military records.\n"
           "     > You can choose to save the records in to a text file "
           "through this option.\n"
           " v - View Military Records\n"
           "     > This option allows you to view properly formatted military\n"
           "       records.\n"
           " e - Encrypt and Compress Records\n"
           "     > This option encrypts and compresses you files.\n"
           "     > The file will be available as a .min file from this option."
           "\n d - Decompress and Decrypt Records\n"
           "     > This option decompress and decrypt you files.\n"
           "     > Your file will be available as a .txt file from this option."
           "\n u - View the Utility Menu (access the Help Menu for more info.)"
           "\n     > This option allows you to access a utility menu that"
           " allows you to\n"
           "       choose whether to compress, decompress, encrypt or decrypt "
           "files.\n"
           " r - View Recent Files\n"
           "     > View the files you recently interacted with.\n"
           "-----------------------------------------------------------------\n"
           "\n");
}

/*Utility Menu for access to functions individually*/
void utilityMenu() {
    printf("Welcome to the Utilities Menu!\n\n");
    int choice;
    int quit=0;
        while (!quit) {
            printf("\n");
            printf("Enter Choice:\n");
            printf("1 - Compress File\n");
            printf("2 - Decompress File\n");
            printf("3 - Encrypt File\n");
            printf("4 - Decrypt File\n");
            printf("5 - Exit\n");
            printf("Enter choice (number between 1-5)>\n");
            fflush(stdin);
            scanf("%d", &choice);
            getchar();


        switch (choice){
            case 1:
                compressOnly();
                break;
            case 2:
                decompressOnly();
                break;
            case 3:
                encryptOnly();
                break;
            case 4:
                decryptOnly();
                break;
            case 5:
                exit(0);
            default:
                printf("Hey! That's an Invalid Choice! Try Again!\n");
                break;
        }
    }
}
            
#endif