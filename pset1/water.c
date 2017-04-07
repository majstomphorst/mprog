/****************************************************************************
 * water.c
 * Programmeren 1 - pset1 - exercise 02
 * By Maxim Stomphorst
 * 
 * Convert showered minutes to bottles of water.
***************************************************************************/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // asking how long the shower took in minutes
    printf("Minutes: ");
    int minutes = get_int();
    
    // printing the amount of bottels used
    printf("Bottles: %i\n", minutes * 12);
}