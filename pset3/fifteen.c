/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          to d x d).
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

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

void swap(int* a, int* b);
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
    FILE* file = fopen("log.txt", "w");
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
        int tile = GetInt();
        
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
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int grid = (d *d)-1;
    for(int i=0; i < d; i++)
    {
        for(int j=0; j < d; j++)
        {
            board [i][j] = grid;
            grid--;
    
        }
    }

    if(((d *d)-1) % 2 != 0)
    {
        board[d-1][d-2] = board[d-1][d-2] ^ board[d-1][d-3];
        board[d-1][d-3] = board[d-1][d-2] ^ board[d-1][d-3];
        board[d-1][d-2] = board[d-1][d-2] ^ board[d-1][d-3];
    }

}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    
    for(int k=0; k < d; k++)
    {
        char x = '_';
        printf("\n");
        for(int l=0; l < d ; l++)
        {
            if(board[k][l] != 0)
            {
            printf("%2d  ", board[k][l]);
            }
            else
            {
                printf("%2c  ", x);
            }
            
        }
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
void swap(int* a, int* b)
{
    *a = *a ^ *b;
    *b = *a ^ *b; 
    *a = *a ^ *b;
}
bool move(int tile)
{
    for(int j=(d-1); j >= 0; j--)
    {
        for(int i=(d-1); i >= 0; i--)
        {
            if(board[j][i] ==0)
            {

                if (tile == board[j][i-1])
                {
                    swap(&board[j][i-1], &board[j][i]);
                    return true;
                }
                if(tile == board[j+1][i] )
                {
                    swap(&board[j+1][i], &board[j][i]);
                    return true;
                }
                if(tile == board[j-1][i])
                {
                    swap(&board[j-1][i], &board[j][i]);
                    return true;
                }
                if(tile == board[j][i+1])
                {
                    swap(&board[j][i+1], &board[j][i]);
                    return true; 
                }
                
            }
        }
    }
   return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int i;
    int j;
    int n = 1;
    
    if(board[0][0] != 1 || board[d-1][d-2] != ((d*d)-1) || board[d-1][d-1] != 0) // come back to them
    {
        return false;
    }
        for(i = 0; i < d; i++)
        
        {
            for(j = 0; j <  d; j++)
            {
                if(board[i][j] != n && n < ((d*d)-1))
                {
                    return false;
                }
                n++;
            }
        }
       
  return true;
}
