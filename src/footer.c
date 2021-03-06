#include <string.h>
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include "footer.h"
#include "header.h"
#include "animal.h"
#include "utils.h"

extern window_settings_t win_set;

void print_footer(WINDOW *win)
{
    getmaxyx(footer_win, win_set.maxFooterHeight, win_set.maxFooterWidth);

    char buf[50];
    int32_t char_ret[5], i = 0;
    uint32_t footer_width = 0;

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
    char_ret[i] = snprintf(buf, sizeof buf, "days: %"PRIu64" days MOD %d: %"PRIu64"", win_set.days, MAX_MOVES, win_set.days % MAX_MOVES);
    color_str(win, 0, ++footer_width, 0, 0, buf);
    footer_width += char_ret[i++];

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "total animals: %d dead animals: %d", win_set.total_animals, count_dead_animals());
    color_str(win, 0, ++footer_width, 0, 0, buf);
    footer_width += char_ret[i++];

    wnoutrefresh(win);
}

