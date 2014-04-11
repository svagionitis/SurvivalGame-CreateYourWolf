#ifndef HEADER_H
#define HEADER_H

#include <curses.h>

#define HEADER_ROWS 1

typedef struct window_settings
{
    int maxWidth;
    int maxHeight;
    int maxHeaderWidth;
    int maxHeaderHeight;
    int maxMainWidth;
    int maxMainHeight;
    int maxFooterWidth;
    int maxFooterHeight;
}window_settings_t;

// Header window
WINDOW *header_win;

void print_header(WINDOW *);

#endif /* HEADER_H */
