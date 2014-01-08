#ifndef S_GAME
#define S_GAME

#include "entity/player.h"
#include "entity/board.h"

int game_select_map(s_board *b);
void game_select_players(s_board *b, s_player *players, int nb_max_players);
// return the winner
s_player *game_start(s_board *b);

#endif
