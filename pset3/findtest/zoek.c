#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int value[9] = {1,3,6,9,10,14,16,17,21};
    int n = 8;
    printf("check: ");
    int check = get_int();
    
    if (check < 0)
    {
        printf("fout");
        return false;
    }
    
    // determining the lowwer an upper boundaries 
    int low = 0;
    int up = n;
    
    // stop when up and low are at the same spot
    while (low <= up)
    {
        // if value is smaller than middel of effective array
        if (check < value[((low + up) / 2)])
        {
            up = ((low + up) / 2);
        }
        // if value is bigger than middel of effective array
        else if (check > value[(((low + up) / 2))])
        {
            low = ((low + up) / 2 + 1);
        }
        else 
        {
            printf("gevonden! %i\n", (low + up) / 2);
            break;
        }
    }
    return 0;
}