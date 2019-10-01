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

#define MAXNUMBER 25
#define MAXINFORMSTION 50


struct record {
	char number [MAXNUMBER+1];
	char information [MAXINFORMATION+1];
};

struct lnode {
       struct record data;
       struct lnode *next;
};

int main() {
	setbuf(stdout, NULL);
	menu();
	return 0;
}



void menu() {
	int choice;
	int quit=0;
        while (!quit) {
		printf ("\n");
		printf ("1.Search\n");
		printf ("2.Creat Entry\n");
		printf ("3.display recently encrypted and compressed files\n");
		printf ("4.Save Entries to Database\n");
		printf ("5.Load Database\n");
		printf ("6.Encrypt Database\n");
		printf ("7.Compress Database\n");
		printf ("8.Decrypt Files\n");
		printf ("9.Decompress Files\n");
		printf ("10.Exit");
		
		printf (""Enter choice (number between 1-10)>\n");
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
		case 8:
			Decrypt ();
			break;
	        case 9:
			Decompress ();
			break;
		case 10:
			quit = 1;
			break;
	        
		default:
			printf("Invalid choice\n");
			break;
		}
	}
}
			
void Search(struct lnode *list){
    char e[MAXWORD];
    struct lnode *r;

        printf("Please input the employee serial number you want to search: ");
        getchar();
        gets(e);

	if((r = SearchPrimarykey(list, e)) != NULL) {
		DisplayRecord;
	} else {
		printf (" Can't find the file ")
	}
}
		
void Readfile() {
	
       
void CreatEntry(){
	file_t new_file;
	char buffer[1000]
	
	
