#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("d = ?:");
    int d = get_int();
    // getting count down for grid
    int count_down = d * d - 1;
    
    // hier kan ik d--; doen das misschien later netter
    
    // creating grid 
    int board[d][d];
    
    for (int y = 0; y <= d - 1; y++)
    {
        for (int x = 0; x <= d - 1; x++)
        {
            board[y][x] = count_down;
            count_down--;
        }
    }
    
    if (d % 2 == 0)
    {
        // swap tile 1 and 2
        board[d - 1][d - 1 - 1] = 2;
        board[d - 1][d - 1 - 2] = 1;
    }
    
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
}

    