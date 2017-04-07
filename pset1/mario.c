/****************************************************************************
 * mario.c More comfortable
 * Programmeren 1 - pset1 - exercise 03
 * By Maxim Stomphorst
 * 
 * Print 2 Mario pyramid's one up and one down with space in between.
***************************************************************************/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // height pyramid
    int height;
    do
    {
        // ask for pyramid height
        printf("height: ");
        height = get_int();
    }
    // restricting user input
    while(height < 0 || height > 23);
    
    // printing the pyramid
    // the fist loop print the enters
    // the inner loops prints the space and hash's
    // first " " second "#" third "  " fourth "#"
    for (int enter = 0; enter != height; enter++)
    {
        for (int space = 0; space != height - enter - 1; space++)
        {
            printf(" ");
        }
        for (int hash = 0; hash != enter + 1; hash++)
        {
            printf("#"); 
        }
       
        printf("  ");
       
        for (int hash = 0; hash != enter + 1; hash++)
        {
            printf("#");
        }
       
        printf("\n");
       
    }
}