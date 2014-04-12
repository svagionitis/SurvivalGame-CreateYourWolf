#ifndef FOOTER_H
#define FOOTER_H

#include <curses.h>

#define FOOTER_ROWS 1

#define MAX_MOVES 20
#define MAX_ATTACKS 10
#define MAX_SURROUNDING_WIDTH 3
#define MAX_SURROUNDING_HEIGHT 3

typedef enum moves {UP, DOWN, RIGHT, LEFT, HOLD, LAST_MOVE} moves_t;
typedef enum attacks {ROCK, PAPER, SCISSORS, SUICIDE, LAST_ATTACK} attacks_t;

typedef struct animal
{
    char type;
    int x;
    int y;
    moves_t moves[MAX_MOVES];
    attacks_t attacks[MAX_ATTACKS];
    char surroundings[MAX_SURROUNDING_WIDTH][MAX_SURROUNDING_HEIGHT];
}animal_t;

// Footer window
WINDOW *footer_win;

void print_footer(WINDOW *);

#endif /* FOOTER_H */
