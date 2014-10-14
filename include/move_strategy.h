#ifndef MOVE_STRATEGY_H
#define MOVE_STRATEGY_H

#define MAX_MOVES 20

typedef enum moves {UP, DOWN, RIGHT, LEFT, HOLD, END_MOVE} moves_t;

typedef void (*move_strategy_t)(moves_t moves[]);

void move_strategy_caller(void (*move_strategy_t)(moves_t []), moves_t moves[]);

void lion_moves(moves_t moves[]);
void bear_moves(moves_t moves[]);
void stone_moves(moves_t moves[]);
void wolf_moves(moves_t moves[]);
void random_moves(moves_t moves[]);

#endif /* MOVE_STRATEGY_H */
