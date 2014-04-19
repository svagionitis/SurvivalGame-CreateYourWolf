#ifndef HEADER_H
#define HEADER_H

#include <curses.h>
#include <stdint.h>

#define HEADER_ROWS 1

typedef struct window_settings
{
    int32_t maxWidth;
    int32_t maxHeight;
    int32_t maxHeaderWidth;
    int32_t maxHeaderHeight;
    int32_t maxAnimalWidth;
    int32_t maxAnimalHeight;
    int32_t maxFooterWidth;
    int32_t maxFooterHeight;
    int8_t c;
    int8_t last_char;
    uint32_t speed;
    uint8_t set_border;
    uint8_t set_surrounding_area;
    uint64_t days;
    int32_t total_animals;
}window_settings_t;

// Header window
WINDOW *header_win;

void print_header(WINDOW *);

#endif /* HEADER_H */
