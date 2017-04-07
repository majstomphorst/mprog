/****************************************************************************
 * vigenere.c
 * Programmeren 01 - pset 02 - exercise 03
 * By Maxim Stomphorst
 * 
 * This converts text to ciphertext with a key that the user give's.
 * But the key is a word in this case.
***************************************************************************/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// the key is given in Command Line Argument (CLA)
int main(int argc, string argv[])
{
    // check if there are 2 CLA
    if (argc != 2)
    {
        // telling the user how the CLA works
        printf("Usage: ./vigenere key\n");
        return 1;
    }
    
    // gowing through 2nd CLA posission for posission
    for (int i = 0 ; i < strlen(argv[1]); i++)
    {
        // checking if ith posission is alphabetical
        if (isalpha(argv[1][i]))
        {
            // converting ith posission to lower case letter
            argv[1][i] = tolower(argv[1][i]);
        }
        else
        {
            // telling the user what to do
            printf("the key must be alphabetical");
            return 1;
        }
    }
    
    // asking user for input
    printf("plaintext: ");
    string text = get_string();

    // converting CLA input to string
    string key = (argv[1]);
    // counting string lenghts
    int text_l = strlen(text);
    int key_l = strlen(key);
    printf("ciphertext: ");
    
    // gowing through text char for char (i)
    // gowing throug key char for char (j) only j++ when used
    for (int i = 0, j = 0; i < text_l; i++)
    {
        // checking if ith char is upper
        if (isupper(text[i]))
        {
            // convert ascii(upper) to alphabet count - 64
            // wrap around key j % key_l  
            // convert ascii(lower) to alphabet count - 97
            // wrap around alphabet % 26 
            // convert alphabet count back to ascii(upper)
            printf("%c",(((text[i] - 'A') + (key[j % key_l] - 'a') ) % 26 ) + 'A');
            // j used so j++ (independent variable for key posission) 
            j++;
        }
        // checking if ith char is lower
        else if (islower(text[i]))
        {
            // every char is lower - 97 no convertion too / from upper
            printf("%c",(((text[i] - 'a') + (key[j % key_l] - 'a') ) % 26 ) + 'a');
            j++;
        }
        else
        {
            // downt convert ith char directly print 
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0;
}