#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "utils.h"

void color_str(WINDOW *win, uint32_t y, uint32_t x, int16_t fg_color, int16_t bg_color, const char *str)
{
    int16_t i;
    // Search all the pair of colors
    // to match with the given one.
    // Then apply the specific pair.
    // Naive way
    for (i = 0;i < COLOR_PAIRS;i++)
    {
        int16_t f, b;
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

void select_percentage_coverage_onscreen(int32_t ret_coverage, double coverage, int32_t maxWidth, int32_t maxHeight)
{
    ret_coverage = (int32_t)(coverage * (double)(maxWidth * maxHeight));
}
