#ifndef S_GAME
#define S_GAME

#include <stdint.h>
#include "entity/player.h"
#include "entity/board.h"

void game_select_map(s_board *b, uint8_t *nb_max_players, uint16_t *pawns_per_player);
void game_select_players(s_board *b, s_player *players, const uint8_t nb_max_players, const uint16_t nb_pawns_per_player);
// return the winner
s_player *game_start(s_board *b);

#endif
