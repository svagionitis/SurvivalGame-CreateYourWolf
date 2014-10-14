#include "move_strategy.h"
#include "utils.h"
#include <stdint.h>
#include <stdlib.h>

void move_strategy_caller(void (*move_strategy_t)(moves_t []), moves_t moves[])
{
    move_strategy_t(moves);
}

void lion_moves(moves_t moves[])
{
    moves[0] = DOWN;
    moves[1] = RIGHT;
}

void bear_moves(moves_t moves[])
{
    moves[0] = DOWN;
    moves[1] = DOWN;
    moves[2] = DOWN;
    moves[3] = DOWN;
    moves[4] = RIGHT;
    moves[5] = RIGHT;
    moves[6] = RIGHT;
    moves[7] = RIGHT;
    moves[8] = UP;
    moves[9] = UP;
    moves[10] = UP;
    moves[11] = UP;
    moves[12] = LEFT;
    moves[13] = LEFT;
    moves[14] = LEFT;
    moves[15] = LEFT;
}

void stone_moves(moves_t moves[])
{
    moves[0] = HOLD;
}

void wolf_moves(moves_t moves[])
{
    // Random moves
    for (uint32_t j = 0;j < MAX_MOVES;j++)
    {
        init_seed_srand();

        moves[j] = rand() % END_MOVE;
    }

}

