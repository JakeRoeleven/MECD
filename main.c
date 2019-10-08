/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 * 	Jake Roeleven - 13246638
 * 	Thomas Coates - 13276922
 * 	Beichen Man   - 12416780
 * 	Zinh AL-Sweedy - 12402677
 * Date Complete:
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/Interface/interface.h"

#define Green "\e[32m"
#define printf(X) printf(Green "%s",X);

void utilityMenu();
void helpMenu();

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
                    printf("Sorry that's not a valid argument!\n");
                    printf("The following arguments are available: \n"
                    	   "-----------------------------------------------------------------\n"
                    	   "h - View the Help Menu\n"
                    	   "c - Create and Save Military Records\n"
                    	   "v - View Military Records\n"
                    	   "e - Encrypt and Compress Records\n"
                    	   "d - Decompress and Decrypt Records\n"
                    	   "u - View the Utility Menu (access the Help Menu for more info...)\n"
                    	   "r - View Recent Files\n"
                    	   "-----------------------------------------------------------------\n");
                    return 0;
            } 
        }
    } 
    else {
        printf("Hey! You didn't pass in an argument! Try Again!\n\n\n");
        return 0;
    }

    printf("\n\n");
    /*Saftey Return*/
	return 0;
}

void helpMenu() {
    
    printf("Welcome to the MECD Help Menu!\n\n");
    printf("The following arguments are available to be passed in: \n"
    	   "-----------------------------------------------------------------\n"
    	   "h - View this Help Menu\n"
    	   "c - Create and Save Military Records\n"
    	   "    > This option allows you to create new military records.\n"
    	   "    > You can choose to save the records in to a text file through\n"
    	   "      this option.\n"
    	   "v - View Military Records\n"
    	   "    > This option allows you to view properly formatted military\n"
    	   "      records.\n"
    	   "e - Encrypt and Compress Records\n"
    	   "    > This option encrypts and compresses you files.\n"
    	   "    > Your file will be avalible as a .min file after this option.\n"
    	   "d - Decompress and Decrypt Records\n"
    	   "    > This option decompress and decrypt you files.\n"
    	   "    > Your file will be avalible as a .txt file after this option.\n"
    	   "u - View the Utility Menu (access the Help Menu for more info...)\n"
    	   "    > This option allows you to access a utility menu that allows you to\n"
    	   "      choose wether to compress, decompress, encrypt or decrypt files.\n"
    	   "r - View Recent Files\n"
    	   "    > View the files you recently interacted with.\n"
    	   "-----------------------------------------------------------------\n");
}



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
			printf("Enter choice (number between 1-10)>\n");
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
			default:
				printf("Hey! That's an Invalid Choice! Try Again!\n");
				break;
		}
	}
}
			
void CreatRecords(struct lnode* list) {
    int i;
    struct record t;
    struct lnode *n, *r;

    printf ("please input the employee serial number:");
    getchar ();
    scanf ("%d", t.number);
	fflush(stdin);
	prinf("please input the data：");
	gets(t.data);
	strcpy((n->data).word, t.number);
	strcpy((n->data).mean, t.data);
	InsertList(list, n);
}
