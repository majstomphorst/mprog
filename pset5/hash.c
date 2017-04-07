#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZEHASHTABLE 65536

int hash (const char *str);

int main (void)
{
    const char *word = get_string();
    unsigned int h = hash(word);
    printf("hash: %u\n",h);
}


int hash (const char *word)
{
    // int hash = tolower(word[0]) - 'a';
    
    int sum = 0;
    int strl = strlen(word);
    
    for (int i = 0; i < strl; i++)
    {
        sum = sum + tolower(word[i]);
    }
    sum = sum % SIZEHASHTABLE;
    
    return sum;
}

// 65536
// 143,091
// http://www.cse.yorku.ca/~oz/hash.html

