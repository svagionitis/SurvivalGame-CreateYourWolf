#ifndef HEADER_H
#define HEADER_H

#include <curses.h>

#define HEADER_ROWS 1

typedef struct window_settings
{
    int maxWidth;
    int maxHeight;
}window_settings_t;

void print_header(WINDOW *);

#endif /* HEADER_H */
