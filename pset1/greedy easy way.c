/******************************* 
 * greedy.c 
 * By Maxim Stomphorst
 * Calculte the number of cons neede to return change
 * Methode used: while loop
 * learn use of ints vs floats 
 *******************************/
 
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float input_float;
    do
    {
        printf("Change: ");
        input_float = get_float();
    }
    while(input_float < 0.0);

    int input_int = (int) roundf(input_float * 100);
  
    int count = 0;
  
    while (input_int >= 25)
    {
        count++;
        // input_int = input_int - 25
        input_int -= 25;
    }
    while (input_int >= 10)
    {
        count++;
        input_int -= 10;  
    }
    while (input_int >= 5)
    {
        count++;
        input_int -= 5;  
    }
    while (input_int >= 1)
    {
        count++;
        input_int -= 1;  
    }
    
    printf("%i\n", count);
    
}