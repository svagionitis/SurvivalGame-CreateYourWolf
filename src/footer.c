#include <string.h>
#include "footer.h"
#include "header.h"
#include "animal.h"
#include "utils.h"

extern window_settings_t win_set;
extern animal_t lion, bear, stone, wolf;

void print_footer(WINDOW *win)
{
    getmaxyx(footer_win, win_set.maxFooterHeight, win_set.maxFooterWidth);

    char buf[50];
    int char_ret[8], i = 0;
    int footer_width = 0;

    wclear(win);

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "char: %c (0x%x)", win_set.last_char, win_set.last_char);
    color_str(win, 0, 0, 0, 0, buf);
    footer_width += char_ret[i++];

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "speed: %d", win_set.speed);
    color_str(win, 0, ++footer_width, 0, 0, buf);
    footer_width += char_ret[i++];

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "days: %d days MOD MAX_MOVES: %d", win_set.days, win_set.days % MAX_MOVES);
    color_str(win, 0, ++footer_width, 0, 0, buf);
    footer_width += char_ret[i++];

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "lion x: %d y: %d attack: %d winner: %d", lion.x, lion.y, lion.attack, lion.winner);
    color_str(win, 0, ++footer_width, 0, 0, buf);
    footer_width += char_ret[i++];

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "bear x: %d y: %d attack: %d winner: %d", bear.x, bear.y, bear.attack, bear.winner);
    color_str(win, 0, ++footer_width, 0, 0, buf);
    footer_width += char_ret[i++];

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "stone x: %d y: %d attack: %d winner: %d", stone.x, stone.y, stone.attack, stone.winner);
    color_str(win, 0, ++footer_width, 0, 0, buf);
    footer_width += char_ret[i++];

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "wolf x: %d y: %d attack: %d winner: %d", wolf.x, wolf.y, wolf.attack, wolf.winner);
    color_str(win, 0, ++footer_width, 0, 0, buf);
    footer_width += char_ret[i++];

    wnoutrefresh(win);
}

