#include <stdlib.h>
#include "header.h"
#include "animal.h"
#include "utils.h"

extern window_settings_t win_set;

void populate_animals(WINDOW *win, double percent_cov)
{
    int32_t winMaxWidth = 0, winMaxHeight = 0;

    getmaxyx(win, winMaxHeight, winMaxWidth);

    calculate_coverage_onscreen(&win_set.total_animals, percent_cov, winMaxWidth, winMaxHeight);

    // Allocate memory for all the animals.
    all_animals = (animal_t *)calloc(win_set.total_animals, sizeof(animal_t));

    for (int32_t i = 0;i<win_set.total_animals;i++)
    {
        // Choose the animal. For now they are evenly
        // chosen
        all_animals[i].kind = i % 4;

        // Initialize moves array
        for (uint32_t j = 0;j<MAX_MOVES;j++)
            all_animals[i].moves[j] = END_MOVE;

        // Initialize attacks array
        for (uint32_t j = 0;j<MAX_ATTACKS;j++)
            all_animals[i].attacks[j] = END_ATTACK;

        switch(all_animals[i].kind)
        {
            case LION:
                all_animals[i].print_type = 'L';

                all_animals[i].moves[0] = DOWN;
                all_animals[i].moves[1] = RIGHT;
                all_animals[i].attacks[0] = PAPER;
                all_animals[i].attacks[1] = SCISSORS;

                break;
            case BEAR:
                all_animals[i].print_type = 'B';

                all_animals[i].moves[0] = DOWN;
                all_animals[i].moves[1] = DOWN;
                all_animals[i].moves[2] = DOWN;
                all_animals[i].moves[3] = DOWN;
                all_animals[i].moves[4] = RIGHT;
                all_animals[i].moves[5] = RIGHT;
                all_animals[i].moves[6] = RIGHT;
                all_animals[i].moves[7] = RIGHT;
                all_animals[i].moves[8] = UP;
                all_animals[i].moves[9] = UP;
                all_animals[i].moves[10] = UP;
                all_animals[i].moves[11] = UP;
                all_animals[i].moves[12] = LEFT;
                all_animals[i].moves[13] = LEFT;
                all_animals[i].moves[14] = LEFT;
                all_animals[i].moves[15] = LEFT;
                all_animals[i].attacks[0] = PAPER;

                break;
            case STONE:
                all_animals[i].print_type = 'S';

                all_animals[i].moves[0] = HOLD;
                all_animals[i].attacks[0] = ROCK;

                break;
            case WOLF:
                all_animals[i].print_type = 'W';

                // Random moves
                for (uint32_t j = 0;j < MAX_MOVES;j++)
                {
                    init_seed_srand();

                    all_animals[i].moves[j] = rand() % END_MOVE;
                }

                // Random attacks
                for (uint32_t j = 0;j < MAX_ATTACKS;j++)
                {
                    init_seed_srand();

                    all_animals[i].attacks[j] = rand() % END_ATTACK;
                }

                break;
            case END_ANIMAL:
                break;
        }

        init_seed_srand();

        all_animals[i].x = winMaxWidth * ((double)rand()/RAND_MAX);
        all_animals[i].y = winMaxHeight * ((double)rand()/RAND_MAX);

        all_animals[i].attack = END_ATTACK;
        all_animals[i].winner = FALSE;
        all_animals[i].looser = FALSE;
        all_animals[i].isdead = FALSE;
    }
}

void print_animal(WINDOW *win, animal_t animal)
{
    color_str(win, animal.y, animal.x, 0, COLOR_BLACK, (const char *)&animal.print_type);

    // Print surrounding of radius MAX_SURROUNDING_RADIUS
    if (win_set.set_surrounding_area)
    {
        for (int32_t i = 1;i <= MAX_SURROUNDING_RADIUS;i++)
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

    for (int32_t i = 0;i<win_set.total_animals;i++)
    {
        print_animal(win, all_animals[i]);
    }

    wnoutrefresh(win);
}

void move_animal(animal_t *animal)
{
    uint32_t index_move = 0;

    if (animal->kind == LION) // Lion has two moves
        index_move = win_set.days % 2;
    else if (animal->kind == BEAR) // Bear has 16 moves
        index_move = win_set.days % 16;
    else if (animal->kind == STONE) // Stone has 1 move
        index_move = win_set.days % 1;
    else if (animal->kind == WOLF) // Wolf has MAX moves
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
        case END_MOVE:
            break;

    }
}

void move_animals()
{
    for (int32_t i = 0;i<win_set.total_animals;i++)
    {
        move_animal(&all_animals[i]);
    }

}

// Calculate which attack to use if it has
// more than one attacks
void choose_attack(animal_t *animal)
{
    switch(animal->kind)
    {
        case LION:
            init_seed_srand();

            animal->attack = animal->attacks[(rand() % 2)];

            break;
        case BEAR:
        case STONE:
            animal->attack = animal->attacks[0];

            break;
        case WOLF:
            init_seed_srand();

            animal->attack = animal->attacks[(rand() % MAX_ATTACKS)];

            break;
        case END_ANIMAL:
            break;
    }
}

void animal_wins(animal_t *a, animal_t *b)
{
    choose_attack(a);
    choose_attack(b);

    // If both animals are alive
    if (!a->isdead && !b->isdead)
    {
        switch(a->attack)
        {
            case ROCK:
                if (b->attack == PAPER)
                {
                    b->winner = TRUE;
                    a->looser = TRUE;
                }
                else if (b->attack == SCISSORS)
                {
                    a->winner = TRUE;
                    b->looser = TRUE;
                }

                break;
            case PAPER:
                if (b->attack == ROCK)
                {
                    a->winner = TRUE;
                    b->looser = TRUE;
                }
                else if (b->attack == SCISSORS)
                {
                    b->winner = TRUE;
                    a->looser = TRUE;
                }

                break;
            case SCISSORS:
                if (b->attack == ROCK)
                {
                    b->winner = TRUE;
                    a->looser = TRUE;
                }
                else if (b->attack == PAPER)
                {
                    a->winner = TRUE;
                    b->looser = TRUE;
                }

                break;
            case SUICIDE:
                break;
            case END_ATTACK:
                break;
        }
    }
    else if (a->isdead && !b->isdead)
    {
        b->winner = TRUE;
        a->looser = TRUE;
    }
    else if (!a->isdead && b->isdead)
    {
        a->winner = TRUE;
        b->looser = TRUE;
    }

    if (a->looser)
    {
        a->isdead = TRUE;
        a->print_type = ' ';
        // Set hold move if dead
        for (uint32_t i = 0;i<MAX_MOVES;i++)
            a->moves[i] = HOLD;
    }
    if (b->looser)
    {
        b->isdead = TRUE;
        b->print_type = ' ';
        for (uint32_t i = 0;i<MAX_MOVES;i++)
            b->moves[i] = HOLD;
    }

    a->winner = FALSE;
    a->looser = FALSE;
    b->winner = FALSE;
    b->looser = FALSE;
}

// Check if two animals collide
char collides(animal_t a, animal_t b)
{
    if (a.x == b.x)
        if (a.y == b.y)
            return TRUE;

    return FALSE;
}

void check_attacks()
{
    // TODO Try to avoid somehow the double for loop
    for (int32_t i = 0;i<win_set.total_animals;i++)
    {
        if (all_animals[i].isdead)
            continue;

        for (int32_t j = 0;j<win_set.total_animals;j++)
        {
            if (i == j)
                continue;

            if (all_animals[j].isdead)
                continue;

            if (collides(all_animals[i], all_animals[j]))
            {
                animal_wins(&all_animals[i], &all_animals[j]);
            }
        }
    }
}

uint32_t count_dead_animals()
{
    uint32_t sum = 0;

    for (int32_t i = 0;i<win_set.total_animals;i++)
    {
        if (all_animals[i].isdead)
            sum += 1;
    }

    return sum;
}
