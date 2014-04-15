#ifndef ANIMAL_H
#define ANIMAL_H

#include <curses.h>

#define MAX_MOVES 20
#define MAX_ATTACKS 10
#define MAX_SURROUNDING_RADIUS 1
#define MAX_LIONS 1
#define MAX_BEARS 1
#define MAX_STONES 1
#define MAX_WOLVES 1

typedef enum moves {UP, DOWN, RIGHT, LEFT, HOLD, LAST_MOVE} moves_t;
// PAPER wins ROCK, ROCK wins SCISSORS, SCISSORS win PAPER,
typedef enum attacks {ROCK, PAPER, SCISSORS, SUICIDE, LAST_ATTACK} attacks_t;

typedef struct animal
{
    char type;
    int x;
    int y;
    moves_t moves[MAX_MOVES];
    attacks_t attacks[MAX_ATTACKS];
    attacks_t attack;
}animal_t;

// Animal window
WINDOW *animal_win;

void populate_lion(void);
void print_animal(WINDOW *, animal_t);
void print_lion(WINDOW *);
void populate_bear(void);
void print_bear(WINDOW *);
void populate_stone(void);
void print_stone(WINDOW *);
void populate_wolf(void);
void print_wolf(WINDOW *);
void print_animals(WINDOW *);
void move_animal(animal_t *);
void attack_animal(animal_t);
attacks_t compare_attacks(attacks_t, attacks_t);
char collides(animal, animal);
void check_attacks();

#endif /* ANIMAL_H */
