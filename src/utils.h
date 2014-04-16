#ifndef UTILS_H
#define UTILS_H

#include <curses.h>
#include <stdint.h>

void color_str(WINDOW *, uint32_t, uint32_t, int16_t, int16_t, const char *);
void init_seed_srand(void);
int32_t select_percentage_coverage_onscreen(double, int32_t, int32_t);

#endif /* UTILS_H */
