#include <string.h>
#include "header.h"
#include "utils.h"

extern window_settings_t win_set;

void print_header(WINDOW *win)
{
    getmaxyx(header_win, win_set.maxHeaderHeight, win_set.maxHeaderWidth);

    char buf[50];
    int char_ret[9], i = 0;
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

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "Animal Max Height: %d", win_set.maxAnimalHeight);
    color_str(win, 0, ++header_width, 0, 0, buf);
    header_width += char_ret[i++];

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "Animal Max Width: %d", win_set.maxAnimalWidth);
    color_str(win, 0, ++header_width, 0, 0, buf);
    header_width += char_ret[i++];

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "Header Max Height: %d", win_set.maxHeaderHeight);
    color_str(win, 0, ++header_width, 0, 0, buf);
    header_width += char_ret[i++];

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "Header Max Width: %d", win_set.maxHeaderWidth);
    color_str(win, 0, ++header_width, 0, 0, buf);
    header_width += char_ret[i++];

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "Footer Max Height: %d", win_set.maxFooterHeight);
    color_str(win, 0, ++header_width, 0, 0, buf);
    header_width += char_ret[i++];

    memset(buf, '\0', sizeof buf);
    char_ret[i] = snprintf(buf, sizeof buf, "Footer Max Width: %d", win_set.maxFooterWidth);
    color_str(win, 0, ++header_width, 0, 0, buf);
    header_width += char_ret[i++];

    wnoutrefresh(win);
}


