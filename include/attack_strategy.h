#ifndef ATTACK_STRATEGY_H
#define ATTACK_STRATEGY_H

#define MAX_ATTACKS 10

// PAPER wins ROCK, ROCK wins SCISSORS, SCISSORS win PAPER,
typedef enum attacks {ROCK, PAPER, SCISSORS, SUICIDE, END_ATTACK} attacks_t;

typedef void (*attack_strategy_t)(attacks_t attacks[]);

void attack_strategy_caller(void (*attack_strategy_t)(attacks_t []), attacks_t attacks[]);

void lion_attacks(attacks_t attacks[]);
void bear_attacks(attacks_t attacks[]);
void stone_attacks(attacks_t attacks[]);
void wolf_attacks(attacks_t attacks[]);

#endif /* ATTACK_STRATEGY_H */
