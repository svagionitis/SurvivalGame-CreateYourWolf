#include "attack_strategy.h"
#include "utils.h"
#include <stdint.h>
#include <stdlib.h>

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

