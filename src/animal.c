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


    lion.moves[0] = DOWN;
    lion.moves[1] = RIGHT;
    lion.attacks[0] = PAPER;
    lion.attacks[1] = SCISSORS;
}

void print_lion(WINDOW *win)
{
    color_str(win, lion.y, lion.x, 0, COLOR_BLACK, "L");
}

void populate_bear(void)
{
    bear.type = 'B';

    // Put random coordinates
    // the first time

    init_seed_srand();

    bear.x = win_set.maxAnimalWidth * ((double)rand()/RAND_MAX);
    bear.y = win_set.maxAnimalHeight * ((double)rand()/RAND_MAX);

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

void print_bear(WINDOW *win)
{
    color_str(win, bear.y, bear.x, 0, COLOR_BLACK, "B");
}

void populate_stone(void)
{
    stone.type = 'S';

    // Put random coordinates
    // the first time

    init_seed_srand();

    stone.x = win_set.maxAnimalWidth * ((double)rand()/RAND_MAX);
    stone.y = win_set.maxAnimalHeight * ((double)rand()/RAND_MAX);

    stone.moves[0] = HOLD;
    stone.attacks[0] = ROCK;
}

void print_stone(WINDOW *win)
{
    color_str(win, stone.y, stone.x, 0, COLOR_BLACK, "S");
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

void print_wolf(WINDOW *win)
{
    color_str(win, wolf.y, wolf.x, 0, COLOR_BLACK, "W");
}


void print_animals(WINDOW *win)
{
    getmaxyx(win, win_set.maxAnimalHeight, win_set.maxAnimalWidth);

    wclear(win);

    print_lion(win);
    print_bear(win);
    print_stone(win);
    print_wolf(win);

    wnoutrefresh(win);
}

