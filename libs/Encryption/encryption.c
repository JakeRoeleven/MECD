#include <stdio.h>  /* printf,scanf ,fgets,fread,fwrite,stdin*/
#include <string.h> /* strlen, strcpy,strncpy,strcmp*/
#include <stdlib.h> /* sizeof,NULL */

/******************************************************************************
 * List preprocessing directives - you may define your own.
******************************************************************************/
/* #define 
 */
/******************************************************************************
 * List structs - definition for struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
******************************************************************************/

/*********************************************************************************
 * Function prototypes - all the prototypes for the functions used in the program
**********************************************************************************/
int encrypt(char input[1000]);
void decrypt(char text[1000], int key);
/* search for func to change the file to plain text to pass it to cipher method */
/******************************************************************************
 * Main: is the main function in the program:
 * in the main function, the program read the choice from the user to know what 
 * is asked for and deal with each choice from the user in the correct way.
 * inputs:
 * - none
 * outputs:
 * - 0 when it finished dealing with the program.
******************************************************************************/
int main(void)
{
    char text[1000];
    int key;
    printf("enter the text you want to cipher: ");
    scanf("%s", text);
    key = encrypt(text);
    decrypt(text, key);

    return 0;
}
int encrypt(char text[1000])
{

    int key;
    int i;

    printf("enter the key: ");
    scanf("%d", &key);
    int len = strlen(text);
    printf("%d", len);
    for (i = 0; text[i] != '\n'; i++)
    {

        if (text[i] == 32)
        {
            text[i] = text[i];
        }
        else if (text[i] >= 'a' && text[i] <= 'z')
        {
            text[i] = (text[i] - 'a' - key + 26) % 26 + 'a';
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            text[i] = (text[i] - 'A' - key + 26) % 26 + 'A';
        }
        printf("%c", text[i]);
    }
    printf("\n");

    return key;
}

void decrypt(char text[1000], int key)
{

    char encryptedtext[1000];
    int i;

    for (i = 0; text[i] != '\0'; i++)
    {
        
        if (text[i] == 32)
        {
            encryptedtext[i] = text[i];
        }
        else if (text[i] >= 'a' && text[i] <= 'z')
        {
            encryptedtext[i] = (text[i] - 'a' - key + 26) % 26 - 'a';
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            encryptedtext[i] = (text[i] - 'A' - key + 26) % 26 - 'A';
        }
        printf("%c", encryptedtext[i]);
    }
    printf("\n");
}