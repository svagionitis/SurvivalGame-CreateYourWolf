#ifndef UTILS_H
#define UTILS_H

#include <curses.h>

void color_str(WINDOW *, int, int, short, short, const char *);
void init_seed_srand(void);

#endif /* UTILS_H */
