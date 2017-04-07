#include <cs50.h>
#include <stdio.h>
#include <string.h> 

int main(void)
{
    int value[8] = {3,5,7,0,2,1,4,6};
    int n = 8;
    
    for (int i = 0; i < n; i++)
    {
        printf("%i-",value[i]);
    }
    printf("\n");
    
    for (int i = 0; i < n; i++)
    {
        int low = i;
        
        for (int j = i; j < n; j++)
        {
            if (value[low] > value[j])
            {
                low = j;
            }
        }
            int swap = value[low];
            value[low] = value[i];
            value[i] = swap;   
    }

    for (int i = 0; i < n; i++)
    {
        printf("%i-",value[i]);
    }
    printf("\n");
}