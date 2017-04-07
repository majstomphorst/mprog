#include <stdio.h>
#define ARR_LEN 10

void unique(int array[], int n);
int main(void)
{
     int array[ARR_LEN] = {1, 1, 1, 1, 1, 1, 1,1,1,1};
     unique(array, ARR_LEN);
     return 0; 
}

void unique(int array[], int n)
{
     int j = 0;
     
     for (int i = 0; i < n; i++)
     {
          for ( ; j < n; j++)
          {
               if(array[i] == array[j])
               {
                    break;
               }
          }
          
          if (i ==j)
          {
               printf("%i",array[i]);
          }
     }
}

















// int unique(int array[], int n)
// {
//      int j = 0;
     
//      for (int i = 0; i < n; i++) 
//      {
//           for (j = 0; j < i; j++)
//           {
//                if (array[i] == array[j])
//                {
//                     break;
//                }
//           }

//           if (i == j)
//           {
//           /* No duplicate element found between index 0 to i */
//           printf("%d\n", array[i]);
//           }
//      }
//      return 0;
// }