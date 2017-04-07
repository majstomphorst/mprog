/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // check if n and or s is pressent if none tel user how to use 
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // converting CLA (n) input to int
    int n = atoi(argv[1]);

    // determining if s was given 
    if (argc == 3)
    {
        // uses s as seed
        srand48((long) atoi(argv[2]));
    }
    // if s is not pressent
    else
    {
        // get the current time of the machine and uses it as seed
        srand48((long) time(NULL));
    }

    // giving n time's a random number
    for (int i = 0; i < n; i++)
    {
        // output drand48 is 0.x to get int do iets times a big number. 
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
