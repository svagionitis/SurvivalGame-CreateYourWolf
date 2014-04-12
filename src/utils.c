#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "utils.h"

void color_str(WINDOW *win, int y, int x, short fg_color, short bg_color, const char *str)
{
    short i;
    // Search all the pair of colors
    // to match with the given one.
    // Then apply the specific pair.
    // Naive way
    for (i = 0;i < COLOR_PAIRS;i++)
    {
        short f, b;
        pair_content(i, &f, &b);
        if (f == fg_color && b == bg_color)
            break;
    }

    wattron(win, COLOR_PAIR(i));

    mvwaddstr(win, y, x, str);

    wattroff(win, COLOR_PAIR(i));
}

void init_seed_srand(void)
{
    struct timeval t;

    // Sleep 10 usec in order 
    // not to have the same seed
    usleep(10);

    gettimeofday(&t, NULL);

    srand(t.tv_usec * t.tv_sec);
}
