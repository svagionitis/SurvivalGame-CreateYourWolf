#include <stdlib.h>
#include "header.h"
#include "animal.h"
#include "utils.h"

extern window_settings_t win_set;
extern animal_t lion, bear, stone, wolf;

void populate_lion(void)
{
    lion.type = 'L';

    // Put random coordinates
    // the first time

    init_seed_srand();

    lion.x = win_set.maxAnimalWidth * ((double)rand()/RAND_MAX);
    lion.y = win_set.maxAnimalHeight * ((double)rand()/RAND_MAX);

    for (int i = 0;i<MAX_MOVES;i++)
        lion.moves[i] = LAST_MOVE;

    lion.moves[0] = DOWN;
    lion.moves[1] = RIGHT;
    lion.attacks[0] = PAPER;
    lion.attacks[1] = SCISSORS;
}

void populate_bear(void)
{
    bear.type = 'B';

    // Put random coordinates
    // the first time

    init_seed_srand();

    bear.x = win_set.maxAnimalWidth * ((double)rand()/RAND_MAX);
    bear.y = win_set.maxAnimalHeight * ((double)rand()/RAND_MAX);

    for (int i = 0;i<MAX_MOVES;i++)
        bear.moves[i] = LAST_MOVE;

    bear.moves[0] = DOWN;
    bear.moves[1] = DOWN;
    bear.moves[2] = DOWN;
    bear.moves[3] = DOWN;
    bear.moves[4] = RIGHT;
    bear.moves[5] = RIGHT;
    bear.moves[6] = RIGHT;
    bear.moves[7] = RIGHT;
    bear.moves[8] = UP;
    bear.moves[9] = UP;
    bear.moves[10] = UP;
    bear.moves[11] = UP;
    bear.moves[12] = LEFT;
    bear.moves[13] = LEFT;
    bear.moves[14] = LEFT;
    bear.moves[15] = LEFT;
    bear.attacks[0] = PAPER;
}

void populate_stone(void)
{
    stone.type = 'S';

    // Put random coordinates
    // the first time

    init_seed_srand();

    stone.x = win_set.maxAnimalWidth * ((double)rand()/RAND_MAX);
    stone.y = win_set.maxAnimalHeight * ((double)rand()/RAND_MAX);

    for (int i = 0;i<MAX_MOVES;i++)
        stone.moves[i] = LAST_MOVE;

    stone.moves[0] = HOLD;
    stone.attacks[0] = ROCK;
}

void populate_wolf(void)
{
    wolf.type = 'W';

    // Put random coordinates
    // the first time

    init_seed_srand();

    wolf.x = win_set.maxAnimalWidth * ((double)rand()/RAND_MAX);
    wolf.y = win_set.maxAnimalHeight * ((double)rand()/RAND_MAX);

    // Random moves
    for (int i = 0;i < MAX_MOVES;i++)
    {
        init_seed_srand();

        wolf.moves[i] = rand() % LAST_MOVE;
    }

    // Random attacks
    for (int j = 0;j < MAX_ATTACKS;j++)
    {
        init_seed_srand();

        wolf.attacks[j] = rand() % LAST_ATTACK;
    }
}

void print_animal(WINDOW *win, animal_t animal)
{
    color_str(win, animal.y, animal.x, 0, COLOR_BLACK, (const char *)&animal.type);

    // Print surrounding of radius MAX_SURROUNDING_RADIUS
    if (win_set.set_surrounding_area)
    {
        for (int i = 1;i <= MAX_SURROUNDING_RADIUS;i++)
        {
            if (animal.x + i < win_set.maxAnimalWidth)
                color_str(win, animal.y, animal.x + i, 0, COLOR_WHITE, " ");

            if (animal.x - i >= 0)
                color_str(win, animal.y, animal.x - i, 0, COLOR_WHITE, " ");

            if (animal.y + i < win_set.maxAnimalHeight)
                color_str(win, animal.y + i, animal.x, 0, COLOR_WHITE, " ");

            if (animal.y - i >= 0)
                color_str(win, animal.y - i, animal.x, 0, COLOR_WHITE, " ");

            if (animal.x + i < win_set.maxAnimalWidth && animal.y + i < win_set.maxAnimalHeight)
                color_str(win, animal.y + i, animal.x + i, 0, COLOR_WHITE, " ");
            if (animal.x + i < win_set.maxAnimalWidth && animal.y - i >= 0)
                color_str(win, animal.y - i, animal.x + i, 0, COLOR_WHITE, " ");
            if (animal.x - i >= 0 && animal.y + i < win_set.maxAnimalHeight)
                color_str(win, animal.y + i, animal.x - i, 0, COLOR_WHITE, " ");
            if (animal.x - i >= 0 && animal.y - i >= 0)
                color_str(win, animal.y - i, animal.x - i, 0, COLOR_WHITE, " ");
        }
    }
}


void print_animals(WINDOW *win)
{
    getmaxyx(win, win_set.maxAnimalHeight, win_set.maxAnimalWidth);

    wclear(win);

    print_animal(win, lion);
    print_animal(win, bear);
    print_animal(win, stone);
    print_animal(win, wolf);

    wnoutrefresh(win);
}

void move_animal(animal_t *animal)
{
    unsigned int index_move = 0;

    if (animal->type == 'L') // Lion has two moves
        index_move = win_set.days % 2;
    else if (animal->type == 'B') // Bear has 16 moves
        index_move = win_set.days % 16;
    else if (animal->type == 'S') // Stone has 1 move
        index_move = win_set.days % 1;
    else if (animal->type == 'W') // Wolf has MAX moves
        index_move = win_set.days % MAX_MOVES;

    switch(animal->moves[index_move])
    {
        case UP:
            animal->y -= 1;

            if (animal->y <= -1)
                animal->y = win_set.maxAnimalHeight;

            break;
        case DOWN:
            animal->y += 1;

            if (animal->y >= win_set.maxAnimalHeight)
                animal->y = 0;

            break;
        case RIGHT:
            animal->x += 1;

            if (animal->x >= win_set.maxAnimalWidth - 1)
                animal->x = 0;

            break;
        case LEFT:
            animal->x -= 1;

            if (animal->x <= 0)
                animal->x = win_set.maxAnimalWidth - 1;

            break;
        case HOLD:
            break;
        case LAST_MOVE:
            break;

    }
}

// Calculate which attack to use if it has
// more than one attacks
void choose_attack(animal_t animal)
{
    switch(animal.type)
    {
        case 'L':
            init_seed_srand();

            animal.attack = animal.attacks[(rand() % 2)];

            break;
        case 'B':
        case 'S':
            animal.attack = animal.attacks[0];

            break;
        case 'W':
            init_seed_srand();

            animal.attack = animal.attacks[(rand() % MAX_ATTACKS)];

            break;
    }
}

void animal_wins(animal_t a, animal_t b)
{
    choose_attack(a);
    choose_attack(b);

    switch(a.attack)
    {
        case ROCK:
            if (b.attack == PAPER)
            {
                b.winner = TRUE;
                a.looser = TRUE;
            }
            else if (b.attack == SCISSORS)
            {
                a.winner = TRUE;
                b.looser = TRUE;
            }

            break;
        case PAPER:
            if (b.attack == ROCK)
            {
                a.winner = TRUE;
                b.looser = TRUE;
            }
            else if (b.attack == SCISSORS)
            {
                b.winner = TRUE;
                a.looser = TRUE;
            }

            break;
        case SCISSORS:
            if (b.attack == ROCK)
            {
                b.winner = TRUE;
                a.looser = TRUE;
            }
            else if (b.attack == PAPER)
            {
                a.winner = TRUE;
                b.looser = TRUE;
            }

            break;
        case SUICIDE:
            break;
        case LAST_ATTACK:
            break;
    }
}

// Check if two animals collide
char collides(animal_t a, animal_t b)
{
    if (a.x == b.x)
        if (a.y == b.y)
            return TRUE;

    if (a.y == b.y)
        if (a.x == b.x)
            return TRUE;

    return FALSE;
}

void check_attacks()
{
    if (collides(lion, bear))
    {
        animal_wins(lion, bear);
    }

    if (collides(lion, stone))
    {
        animal_wins(lion, stone);
    }

    if (collides(lion, wolf))
    {
        animal_wins(lion, wolf);
    }

    if (collides(bear, stone))
    {
        animal_wins(bear, stone);
    }

    if (collides(bear, wolf))
    {
        animal_wins(bear, wolf);
    }

    if (collides(stone, wolf))
    {
        animal_wins(stone, wolf);
    }

}
