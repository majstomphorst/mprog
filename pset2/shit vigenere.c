/****************************************************************************
 * vigenere.c
 * Programmeren 01 - pset 02 - exercise 03
 * By Maxim Stomphorst
 *
 * DOES NOT WORK!
 * 
 * Ben de afgelopen week ziek geweest van zo 12-02 t/m vr 17-02 
 * Vrijdag met paracetamol de opdrachten gemaakt.
 * 
 * This converts plain test to ciphertext with a key that the user give's.
 * But the key is a word in this case.
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
        printf("Usage: ./vigenere key\n");
        return 1;
    }

    // asking user for input
    printf("plaintext: ");
    string plaintext = get_string();

    // converting CLA input to string
    string key = (argv[1]);
    /* Er moet nog een check gemaakt worden om te kijken of de string wel enkel letters bestaad en of ze allemaal klein zijn.
    hier had ik geen tijd voor \
    */
    // counting string lenghts
    int key_lenght = strlen(key);
    int plain_lenght = strlen(plaintext);
    printf("ciphertext: ");
    
    /*
    Normaal zou ik deze(key_a_char) in de for-loop zetten 
    maar dat lukte niet 
    ik had tewijnig tijd om me hier druk over te maken.
    */
    int key_a_char;
    
    // gowing through plaintext char for char
    for (int i = 0, j = 0; i < plain_lenght; i++)
    {
        /*
        De 2 zouden beter zo kunnen:
        key_a_char = (key[j % key_lenght] - 97);
        Maar voor debug redenen wilde ik ze uit elkaar houden.
        */
        // j is a independent int that points to the jth char in key only j++ when j is used
        j = j % key_lenght;
        key_a_char = key[j] - 97;
        
        // checking if ith char is capitilised
        if (isupper(plaintext[i]))
        {
            // printing the int of key[jth] for bebuging
            // i wanted to see if key was correct
            // and that part seems to work
            printf("1: %i\n", key_a_char);
            
            /*formule:
            plaintext[i] - 64(64='A') = ascii to alphabet positions
            than the key_a_char erbij die al op alphabet positions staat.
            + 64 naar ascii
            convertion compleet  printen 
            
            deze formule moet naar mijn inzien werken.
            Als ik plaintext "THIS" of "THIS... TH IS50" invoer key "ohai"
            werkt hij met enkel hoofdletters.
            
            denk dat er iets fout is met de formule maar ik zie het niet.
            */
            printf("%c", (((plaintext[i] - 64) + key_a_char) % 26) + 64);
            // j is used so j++ (independent variable for key_a_char)
            j++;
        }
        // checking if ith char is lowercase
        else if (islower(plaintext[i]))
        {
            
            // printing the int of key[jth] for bebuging
            // i wanted to see if key was correct
            // and that part seems to work
            printf("1: %i\n", key_a_char);
            // tolower heb ik gedaan als test de 64 was 97 'a' 'A'
            printf("%c", tolower((((plaintext[i] - 64) + key_a_char) % 26) + 64));
            // j is used so j++ (independent variable for key_a_char)
            j++;
        }
        // if not upper neither lower downt convert juse print
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}
