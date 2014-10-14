#include "attack_strategy.h"
#include "utils.h"
#include <stdlib.h>

uint32_t count_attacks(attacks_t attacks[])
{
    uint32_t counter = 0;
    for (uint32_t i = 0;i < MAX_ATTACKS;i++)
    {
        if (attacks[i] == END_ATTACK)
            break;

        counter++;
    }

    return counter;
}

void attack_strategy_caller(void (*attack_strategy_t)(attacks_t []), attacks_t attacks[])
{
    attack_strategy_t(attacks);
}

void lion_attacks(attacks_t attacks[])
{
    attacks[0] = PAPER;
    attacks[1] = SCISSORS;
}

void bear_attacks(attacks_t attacks[])
{
    attacks[0] = PAPER;
}

void stone_attacks(attacks_t attacks[])
{
    attacks[0] = ROCK;
}

void wolf_attacks(attacks_t attacks[])
{
    // Random attacks
    for (uint32_t j = 0;j < MAX_ATTACKS;j++)
    {
        init_seed_srand();

        attacks[j] = rand() % END_ATTACK;
    }
}

