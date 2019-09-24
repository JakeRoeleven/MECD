/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 * 	Jake Roeleven
 * Date Complete:
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
	return 0;
}

void menu() {
	int choice;
	int quit=0;
        while (!quit) {
		printf ("\n");
		printf ("Search\n");
		printf ("Creat Entry\n");
		printf ("display recently encrypted and compressed files\n");
		printf ("Save Entries to Database\n");
		printf ("Load Database\n");
		printf ("Encrypt Database\n");
		printf ("Compress Database\n");
			
		printf (""Enter choice (number between 1-5)>\n");
		scanf ("&d", choice);
		
		switch (choice){
	              case 1:
			Search ();
			break;
		      case 2:
			CreatEntry ();
			break;
		      case 3:
			Displayfiles ();
			break;
			
			
	return 0;
}

void CreatEntry(){
	file_t new_file;
	char buffer[1000]
	
	
