/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// white space y and x as for function move
int w_y;
int w_x;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(900000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // keeping track of white space needed for function move
    w_y = d - 1;
    w_x = d - 1;
    // getting highest number of board
    int count_down = d * d - 1;
    
    // filling the board
    // select first y as than fill x as and move to next x
    for (int y = 0; y < d; y++)
    {
        for (int x = 0; x < d; x++)
        {
            // place number in board 
            board[y][x] = count_down;
            // decrease count_down with 1 
            count_down--;
        }
    }
    
    // if the board is even
    if (d % 2 == 0)
    {
        // swap tile 1 and 2
        board[d - 1][d - 2] = 2;
        board[d - 1][d - 3] = 1;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // drawing the board 
    // for loop in for loop to draw the board
    for (int y = 0; y < d; y++)
    {
        // for aesthetics
        printf("\n");
        
        for (int x = 0; x < d; x++)
        {
            // print board value
            if (board[y][x] != 0)
            {
                printf("%2i ",board[y][x]); 
                
            }
            // if board value is 0 print " _ "
            else 
            {
                printf(" _ ");
            }
        }
        // move to next line
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // check if the value the user gives is in the board (negative is check)
    if (tile > (d * d - 1))
    {
        return false;
    }
    
    // check for each coordinate if move is legal, then move white tile
    // check if up coordinate is legal
    if (tile == board[w_y - 1][w_x])
    {
        // give white tile the value that the user gave (tile)
        board[w_y][w_x] = tile;
        // give the place of (old) tile 0 (white)
        board[w_y - 1][w_x] = 0;
        // keep track of the white space
        w_y--;
        return true;
    }
    // check if down coordinate is legal
    else if (tile == board[w_y + 1][w_x])
    {
        board[w_y][w_x] = tile;
        board[w_y + 1][w_x] = 0;
        w_y++;
        return true;
    }
    // check if left coordinate is legal
    else if (tile == board[w_y][w_x - 1])
    {
        board[w_y][w_x] = tile;
        board[w_y][w_x - 1] = 0;
        w_x--;
        return true;
    }
    // check if right coordinate is legal
    else if (tile == board[w_y][w_x + 1])
    {
        board[w_y][w_x] = tile;
        board[w_y][w_x + 1] = 0;
        w_x++;
        return true;
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // making a counter won first tile on the board must be one
    int won = 1;

    // check for win
    // select first y as than scan x as and move to next y
    for (int y = 0; y <= d - 1; y++)
    {
        for (int x = 0; x <= d - 1; x++)
        {
            // if board is in order and last place on the board is 0 won++
            if (board[y][x] == won && board[d - 1][d - 1] == 0)
            {
                won++;
            }
        }
    }
    // if won is as high as the place's on the board
    if (won == d * d)
    {
        return true;
    }
    else
    {
        return false;   
    }
}
