#include <string.h>
#include "header.h"
#include "utils.h"

extern window_settings_t win_set;

void print_header(WINDOW *win)
{
    char buf[50];
    int char_ret[3], i = 0;
    int header_width = 0;

    wclear(win);

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "Max Height: %d", win_set.maxHeight);
    color_str(win, 0, 0, 0, 0, buf);
    header_width += char_ret[i++];

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "Max Width: %d", win_set.maxWidth);
    color_str(win, 0, ++header_width, 0, 0, buf);
    header_width += char_ret[i++];

    wnoutrefresh(win);
}


