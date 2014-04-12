/*Build: gcc -D_BSD_SOURCE -std=c99 -o wolf main.c -lncurses -lpthread*/
/*Source http://codegolf.stackexchange.com/questions/25347/survival-game-create-your-wolf*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <pthread.h>
#include "utils.h"
#include "header.h"
#include "footer.h"
#include "control.h"

#define MAX_MOVES 20
#define MAX_ATTACKS 10
#define MAX_LIONS 1
#define MAX_BEARS 1
#define MAX_STONES 1
#define MAX_WOLVES 1
#define MAX_SURROUNDING_WIDTH 3
#define MAX_SURROUNDING_HEIGHT 3

window_settings_t win_set;
WINDOW *main_win;

typedef enum moves {UP, DOWN, RIGHT, LEFT, HOLD, LAST_MOVE} moves_t;
typedef enum attacks {ROCK, PAPER, SCISSORS, SUICIDE, LAST_ATTACK} attacks_t;

typedef struct animal
{
    char type;
    int x;
    int y;
    moves_t moves[MAX_MOVES];
    attacks_t attacks[MAX_ATTACKS];
    char surroundings[MAX_SURROUNDING_WIDTH][MAX_SURROUNDING_HEIGHT];
}animal_t;

animal_t lion, bear, stone, wolf;

void populate_lion(void)
{
    lion.type = 'L';

    // Put random coordinates
    // the first time

    init_seed_srand();

    lion.x = win_set.maxMainWidth * ((double)rand()/RAND_MAX);
    lion.y = win_set.maxMainHeight * ((double)rand()/RAND_MAX);


    lion.moves[0] = DOWN;
    lion.moves[1] = RIGHT;
    lion.attacks[0] = PAPER;
    lion.attacks[1] = SCISSORS;
}

void print_lion(void)
{
    color_str(main_win, lion.y, lion.x, 0, COLOR_BLACK, "L");
}

void populate_bear(void)
{
    bear.type = 'B';

    // Put random coordinates
    // the first time

    init_seed_srand();

    bear.x = win_set.maxMainWidth * ((double)rand()/RAND_MAX);
    bear.y = win_set.maxMainHeight * ((double)rand()/RAND_MAX);

    bear.moves[0] = DOWN;
    bear.moves[1] = DOWN;
    bear.moves[2] = DOWN;
    bear.moves[3] = DOWN;
    bear.moves[4] = RIGHT;
    bear.moves[5] = RIGHT;
    bear.moves[6] = RIGHT;
    bear.moves[7] = RIGHT;
    bear.moves[8] = UP;
    bear.moves[9] = UP;
    bear.moves[10] = UP;
    bear.moves[11] = UP;
    bear.moves[12] = LEFT;
    bear.moves[13] = LEFT;
    bear.moves[14] = LEFT;
    bear.moves[15] = LEFT;
    bear.attacks[0] = PAPER;
}

void print_bear(void)
{
    color_str(main_win, bear.y, bear.x, 0, COLOR_BLACK, "B");
}

void populate_stone(void)
{
    stone.type = 'S';

    // Put random coordinates
    // the first time

    init_seed_srand();

    stone.x = win_set.maxMainWidth * ((double)rand()/RAND_MAX);
    stone.y = win_set.maxMainHeight * ((double)rand()/RAND_MAX);

    stone.moves[0] = HOLD;
    stone.attacks[0] = ROCK;
}

void print_stone(void)
{
    color_str(main_win, stone.y, stone.x, 0, COLOR_BLACK, "S");
}

void populate_wolf(void)
{
    wolf.type = 'W';

    // Put random coordinates
    // the first time

    init_seed_srand();

    wolf.x = win_set.maxMainWidth * ((double)rand()/RAND_MAX);
    wolf.y = win_set.maxMainHeight * ((double)rand()/RAND_MAX);

    // Random moves
    for (int i = 0;i < MAX_MOVES;i++)
    {
        init_seed_srand();

        wolf.moves[i] = rand() % LAST_MOVE;
    }

    // Random attacks
    for (int j = 0;j < MAX_ATTACKS;j++)
    {
        init_seed_srand();

        wolf.attacks[j] = rand() % LAST_ATTACK;
    }


}

void print_wolf(void)
{
    color_str(main_win, wolf.y, wolf.x, 0, COLOR_BLACK, "W");
}


int main(int argc, char *argv[])
{
    pthread_t thread_control;

    memset(&win_set, 0, sizeof win_set);
    win_set.speed = 100000;

    if (argc != 1)
    {
        printf("Usage: %s\n", argv[0]);
        return -1;
    }

    initscr();

    // Get the maximum size of the screen
    getmaxyx(stdscr, win_set.maxHeight, win_set.maxWidth);

    // Create window for the header rows
    header_win = newwin(HEADER_ROWS, win_set.maxWidth, 0, 0);

    // Create window for the footer rows
    footer_win = newwin(FOOTER_ROWS, win_set.maxWidth, win_set.maxHeight - FOOTER_ROWS, 0);

    // Create main window, it's between the header and the footer
    main_win = newwin(win_set.maxWidth - HEADER_ROWS - FOOTER_ROWS, win_set.maxWidth, HEADER_ROWS, 0);

    getmaxyx(header_win, win_set.maxHeaderHeight, win_set.maxHeaderWidth);
    getmaxyx(footer_win, win_set.maxFooterHeight, win_set.maxFooterWidth);
    getmaxyx(main_win, win_set.maxMainHeight, win_set.maxMainWidth);

    // Check if colors are supported
    if (!has_colors())
    {
        delwin(stdscr);
        endwin();
        fprintf(stderr,"Your terminal does not support color\n");
        return -1;
    }
    else
    {
        // Initialize colors
        start_color();

        // Assign terminal default foreground/background colors to color number -1
        use_default_colors();

        // Initialize color pairs.
        short pair_count = 0;
        for(short i = 0;i<COLORS;i++)
            for(short j = 0;j<COLORS;j++)
                init_pair(pair_count++, i, j);
    }


    clear();

    // The timeout and wtimeout routines set blocking or non-blocking 
    // read for a given window. If delay is negative, blocking read is used 
    // (i.e., waits indefinitely for input). If delay is zero, then non-blocking 
    // read is used (i.e., read returns ERR if no input is waiting). If delay is 
    // positive, then read blocks for delay milliseconds, and returns ERR 
    // if there is still no input.
    timeout(0);
    // Turn off key echoing
    noecho();
    // Line buffering disabled
    cbreak();
    // This determines the visibility of the cursor.
    curs_set(FALSE);
    // Tell curses not to do NL->CR/NL on output
    nonl();
    // Enable the keypad for non-char keys
    keypad(stdscr, TRUE);

    // Populate animals with characteristics
    populate_lion();
    populate_bear();
    populate_stone();
    populate_wolf();

    // Put control in a separate thread
    pthread_create(&thread_control, NULL, control, NULL);

    while(win_set.c != 'q')
    {
        print_header(header_win);

        print_footer(footer_win);


        doupdate();
        usleep(win_set.speed);
    }

    pthread_join(thread_control, NULL);

    delwin(header_win);
    delwin(footer_win);
    endwin();

    return 0;
}
