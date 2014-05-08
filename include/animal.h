#ifndef ANIMAL_H
#define ANIMAL_H

#include <curses.h>
#include <stdint.h>

#define MAX_ANIMALS 4
#define MAX_MOVES 20
#define MAX_ATTACKS 10
#define MAX_SURROUNDING_RADIUS 1
#define MAX_LIONS 1
#define MAX_BEARS 1
#define MAX_STONES 1
#define MAX_WOLVES 1

#define DEAD_ANIMAL_PRINT '\0'

typedef enum moves {UP, DOWN, RIGHT, LEFT, HOLD, END_MOVE} moves_t;

// PAPER wins ROCK, ROCK wins SCISSORS, SCISSORS win PAPER,
typedef enum attacks {ROCK, PAPER, SCISSORS, SUICIDE, END_ATTACK} attacks_t;

// Kind of animals that can be used.
typedef enum animal_kind {LION, BEAR, STONE, WOLF, END_ANIMAL} animal_kind_t;

// The sum should always be 1.0
static double ANIMAL_PERCENT_COVERAGE[MAX_ANIMALS] = {0.25, 0.25, 0.25, 0.25};

typedef struct animal
{
    int8_t print_type;
    animal_kind_t kind;
    int32_t x;
    int32_t y;
    moves_t moves[MAX_MOVES];
    attacks_t attacks[MAX_ATTACKS];
    attacks_t attack;
    uint8_t winner;
    uint8_t looser;
    uint8_t isdead;
}animal_t;

animal_t *all_animals;

// Animal window
WINDOW *animal_win;

void populate_animals(WINDOW *, double);
void print_animal(WINDOW *, animal_t);
void print_animals(WINDOW *);
void move_animal(animal_t *);
void move_animals();
void choose_attack(animal_t *);
void animal_wins(animal_t *, animal_t *);
char collides(animal_t, animal_t);
void check_attacks();
uint32_t count_dead_animals();

#endif /* ANIMAL_H */
