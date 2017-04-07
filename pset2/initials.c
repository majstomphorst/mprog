/****************************************************************************
 * initials.c More comfortable
 * Programmeren 01 - pset 02 - exercise 01
 * By Maxim Stomphorst
 * 
 * The input is the user fist and second name.
 * The output are the users initials.
***************************************************************************/

#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

int main(void)
{
    // getting input and verifying input
    string name = get_string();
    if (name == NULL)
    {
        return -1;
    }
        
    // counting string lenght
    int name_lenght = strlen(name);

    // printf fist char if there is one
    if (name[0] != ' ')
    {
        printf("%c",toupper(name[0]));
    }
    
    // checking char for char staring at 1 because 0 is already checked
    for (int i = 1; i < name_lenght; i++)
    {
        // if current char neither char before is space that print ith char
        if (name[i - 1] == ' ' && name[i] != ' ')
        {
            printf("%c", toupper(name[i]));
        }
    }
    printf("\n");
    return 0;
}