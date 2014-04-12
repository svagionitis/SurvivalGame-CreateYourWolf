#include <string.h>
#include "footer.h"
#include "header.h"
#include "utils.h"

extern window_settings_t win_set;

void print_footer(WINDOW *win)
{
    char buf[50];
    int char_ret[3], i = 0;
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

    wnoutrefresh(win);
}

