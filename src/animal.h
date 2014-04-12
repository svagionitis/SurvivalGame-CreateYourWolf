#ifndef ANIMAL_H
#define ANIMAL_H

#include <curses.h>

#define MAX_MOVES 20
#define MAX_ATTACKS 10
#define MAX_SURROUNDING_WIDTH 3
#define MAX_SURROUNDING_HEIGHT 3
#define MAX_LIONS 1
#define MAX_BEARS 1
#define MAX_STONES 1
#define MAX_WOLVES 1

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

// Animal window
WINDOW *animal_win;

void populate_lion(void);
void print_lion(WINDOW *);
void populate_bear(void);
void print_bear(WINDOW *);
void populate_stone(void);
void print_stone(WINDOW *);
void populate_wolf(void);
void print_wolf(WINDOW *);
void print_animals(WINDOW *);

#endif /* ANIMAL_H */
