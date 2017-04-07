#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 50

int convert(char array[]);

int main(void)
{
     char word[MAX_LEN] = "To Be Converted";
     printf("Number of conversions: %i\n", convert(word));
     printf("Converted string: %s\n", word);
     return 0;
}

int convert(char array[])
{
     int count = 0;
     
     for (int i = 0; i< MAX_LEN; i++)
     {
          if(isupper(array[i]))
          {
               count++;
               array[i] = tolower(array[i]);
               return array[i];
          }
     }
     return count;
}
