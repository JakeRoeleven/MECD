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

#include "libs/Interface/interface.c"

void menu();

int main() {
	menu();
	return 0;
}



void menu() {
	int choice;
	int quit=0;
        while (!quit) {
			/*TODO: Menu function */
			printf("\n");
			printf("Enter Choice:\n");
			printf("1 - Compress File\n");
			printf("2 - Decompress File\n");
			printf("Enter choice (number between 1-10)>\n");
			scanf("%d", &choice);

		switch (choice){
	        case 1:
				compressOnly();
			case 2:
				decompressOnly();
			default:
				printf("Invalid choice\n");
				break;
		}
	}
}
			
