#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("d = ");
    int d = get_int();
    // getting count down for grid
    // int count_down = d * d - 1
    // hier kan ik d--; doen das misschien later netter
    
    // creating grid 
    int board[4][4] = {
    {1,2,3,4} ,
    {5,6,7,8} ,
    {9,10,11,12},
    {13,14,15},
    };
    // find whitespace
    int wht_y;
    int wht_x;
    
    for (int y = 0; y <= d - 1; y++)
    {
        for (int x = 0; x <= d - 1; x++)
        {
            if (board[y][x] == 0)
            {
                wht_y = y;
                wht_x = x;
            }
        }
    }
    
    printf("wht_y = %i\n",wht_y);
    printf("wht_x = %i\n",wht_x);
    
    for (int y = 0; y <= d - 1; y++)
    {
        for (int x = 0; x <= d - 1; x++)
        {
            if (board[y][x] == 0)
            {
                printf(" ");
            }
            else 
            {
               printf("%2i ",board[y][x]); 
            }
            
        }
        printf("\n");
    }
    
    int won = 1;
    // check for win
    for (int y = 0; y < d; y++)
    {
        for (int x = 0; x < d; x++)
        {
            printf("board:%i", board[y][x]);
            if (board[y][x] == won && board[d-1][d-1] == 0)
            {
                
                //printf("won:%i", won);
                won++;
                if( won == d * d)
                {
                    printf("gewonnen!\n");
                    break;
                }
            }
        }
    }
}

    