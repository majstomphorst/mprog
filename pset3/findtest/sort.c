#include <cs50.h>
#include <stdio.h>
#include <string.h> 

int main(void)
{
    
    int n = 5;
    int values[5] = {3,6,1,1,3};
    
    // prints unsorted array
    for (int i = 0; i < n; i++)
    {
        printf("%i-",values[i]);
    }
    printf("\n");
    
    // filling array with zero's
    int index[20] = {0};
    
    // indexing values array (filling index array)
    for (int i = 0; i < n ;i++)
    {
        index[values[i]]++;
    }
    
    // i = possision values sorted (new)
    // j = waarde van index arry
    // k = possision index array
    
    for (int i = 0, j = 0; j < 20; j++)
    {
        for (int k = 0; k < index[j]; k++)
        {
            values[i] = j;
            i++;
        }
    }
    
    
    /*
    for (int i = 0; i < n; i++)
    {
        int low = i;
        
        for (int j = i; j < n; j++)
        {
            if (values[low] > value[j])
            {
                low = j;
            }
        }
            int swap = values[low];
            values[low] = values[i];
            values[i] = swap;   
    }
    */
    
    // print (swap) sort array
    for (int i = 0; i < 20; i++)
    {
        printf("%i-",index[i]);
    }
    printf("\n");
    
     // print sorted array
    for (int i = 0; i < n; i++)
    {
        printf("%i-",values[i]);
    }
    printf("\n");

}