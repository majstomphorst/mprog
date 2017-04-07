/****************************************************************************
 * caesar.c
 * Programmeren 01 - pset 02 - exercise 02
 * By Maxim Stomphorst
 * 
 * This converts plain tekst to ciphertext with a key that the user give's.
 * The key most be a postive integer. 
***************************************************************************/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// the key is given in de command 
int main(int argc, string argv[])
{
    // check if there are 2 Command Line Arguments 
    if (argc != 2)
    {
        // telling the user how the CLA works
        printf("Usage: ./caesar k\n");
        return 1;
    }
    
    // converting CLA input to int 
    int key = (atoi(argv[1]));
    // checking if key is not negative
    if (key < 0)
    {
        return 3;
    }
    
    // asking user for input 
    printf("plaintext: ");
    string plaintext = get_string();
    
    // counting string lenght
    int plain_lenght = strlen(plaintext);
    
    printf("ciphertext: ");
    
    // gowing through plaintext char for char
    for (int i = 0; i < plain_lenght; i++)
    {
        // checking if ith char is in the alphabet 
        if (isalpha(plaintext[i]))
        {
            // checking if ith char is capitalised 
            if (isupper(plaintext[i]))
            {
                // converting ascii to alphabet positions (- 64 = char 'a')
                // than adding the key modulo for wrapping aroud the alphabet
                // than back to ascii and printing encrypted char 
                printf("%c", (((plaintext[i] - 64) + key) % 26) + 64);
            }
            // if ith is lowercase
            else
            {
                // converting ascii to alphabet positions (- 97 = char 'A')
                // than adding the key modulo for wrapping aroud the alphabet
                // than back to ascii and printing encrypted char 
                printf("%c", (((plaintext[i] - 97) + key) % 26) + 97);
            }
        }
        // if ith char is not in the alphabet
        else
        {
            // print ith char
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}