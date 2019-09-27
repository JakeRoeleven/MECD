/*******************************************************************************
 * 48430 Fundamentals of C Programming - Group Assignment
 * Authors:
 * Jake Roeleven - 13246638
 * Thomas Coates - 13276922
 * Beichen Man   - 12416780
 * Zinh AL-Sweedy - 12402677
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
			
		printf (""Enter choice (number between 1-7)>\n");
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
		case 4:
			Save ();
			break;
		case 5:
			Load ();
			break;
		case 6:
			Encrypt ();
			break;
	        case 7:
			Compress ();
			Break;	
	return 0;
}

void Search(){
	
void CreatEntry(){
	file_t new_file;
	char buffer[1000]
	
	
