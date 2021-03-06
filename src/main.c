/*Build: gcc -D_BSD_SOURCE -std=c99 -o wolf main.c -lncurses -lpthread*/
/*Source http://codegolf.stackexchange.com/questions/25347/survival-game-create-your-wolf*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <pthread.h>
#include <stdint.h>
#include "utils.h"
#include "header.h"
#include "footer.h"
#include "control.h"
#include "animal.h"

window_settings_t win_set;
WINDOW *main_win;


int main(int argc, char *argv[])
{
    pthread_t thread_control;

    memset(&win_set, 0, sizeof win_set);
    win_set.speed = 1000000;

    if (argc != 2)
    {
        printf("Usage: %s [percent coverage of screen with animals]\n", argv[0]);
        printf("Example: %s 0.1\n", argv[0]);
        return -1;
    }

    double percent_coverage = atof(argv[1]);
    if (percent_coverage > 1.0 || percent_coverage <= 0.0)
    {
        printf("Value should be between 0.0 and 1.0\n");
        return -1;
    }

    initscr();

    // Get the maximum size of the screen
    getmaxyx(stdscr, win_set.maxHeight, win_set.maxWidth);

    // Create window for the header rows
    header_win = newwin(HEADER_ROWS, win_set.maxWidth, 0, 0);

    getmaxyx(header_win, win_set.maxHeaderHeight, win_set.maxHeaderWidth);

    // Create window for the footer rows
    footer_win = newwin(FOOTER_ROWS, win_set.maxWidth, win_set.maxHeight - FOOTER_ROWS, 0);

    getmaxyx(footer_win, win_set.maxFooterHeight, win_set.maxFooterWidth);

    // Create main window, it's between the header and the footer
    animal_win = newwin(win_set.maxHeight - HEADER_ROWS - FOOTER_ROWS, win_set.maxWidth, HEADER_ROWS, 0);

    getmaxyx(animal_win, win_set.maxAnimalHeight, win_set.maxAnimalWidth);

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
        uint16_t pair_count = 0;
        for(uint16_t i = 0;i<COLORS;i++)
            for(uint16_t j = 0;j<COLORS;j++)
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

    // Populate animals in the precent_coverage*100 of screen
    populate_animals(animal_win, percent_coverage);


    // Put control in a separate thread
    pthread_create(&thread_control, NULL, control, NULL);

    while(win_set.c != 'q')
    {
        print_header(header_win);

        print_animals(animal_win);

        move_animals();

        check_attacks();

        print_footer(footer_win);

        win_set.days++;

        doupdate();
        usleep(win_set.speed);
    }

    if (all_animals)
        free(all_animals);

    pthread_join(thread_control, NULL);

    delwin(header_win);
    delwin(footer_win);
    endwin();

    return 0;
}
